const { partition, uniq } = require("lodash");
const { Converter, TypeScript, ReflectionKind, ParameterType } = require("typedoc");

function filterMap(
    arr,
    fn
) {
    const result = [];

    arr.forEach((item, index) => {
        const newItem = fn(item, index);
        if (newItem !== void 0) {
            result.push(newItem);
        }
    });

    return result;
}

function wildTest(pattern, str) {
    const w = pattern.replace(/[.+^${}()|[\]\\]/g, "\\$&");
    return str.search(`^${pattern.replace(/\*/g, ".*").replace(/\?/g, '.')}$`) !== -1;
}

exports.load = function(application) {
    application.options.addDeclaration({
        type: ParameterType.Array,
        name: "excludeReflections"
    });

    application.converter.on(
        Converter.EVENT_RESOLVE_BEGIN,
        onBeginResolve
    );

    function onBeginResolve(context) {
        const excludeReflections = application.options.getValue("excludeReflections");
        const project = context.project;
        const reflections = Object.values(project.reflections);

        // Remove hidden reflections
        const hidden = reflections.filter((reflection) => {
            for(const excl of excludeReflections) {
                if(wildTest(excl, reflection.getFullName())) return true;
            }
            return false;
        });
        hidden.forEach((reflection) => project.removeReflection(reflection));

        // remove functions with empty signatures after their signatures have been removed
        const [allRemoved, someRemoved] = partition(
            filterMap(hidden, (reflection) =>
                reflection.parent?.kindOf(
                    ReflectionKind.FunctionOrMethod | ReflectionKind.Constructor
                )
                    ? reflection.parent
                    : void 0
            ),
            (method) => method.signatures?.length === 0
        );
        allRemoved.forEach((reflection) =>
            project.removeReflection(reflection)
        );
        someRemoved.forEach((reflection) => {
            reflection.sources = uniq(
                reflection.signatures.reduce(
                    (c, s) => c.concat(s.sources || []),
                    []
                )
            );
        });
    }
};
