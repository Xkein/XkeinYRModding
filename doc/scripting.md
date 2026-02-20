# TypeScript

Recommended tsc version: 5.9.3

You can check the tsc version by command: `tsc --version`


## Working Directory
Recommended working directory: `<game dir>/assets/typescript`

Recommended `tsconfig.json`:
```json
{
    "compilerOptions": {
        "target": "esnext",
        "module": "commonjs",
        "sourceMap": true,
        "experimentalDecorators": true,                   /* Enable experimental support for legacy experimental decorators. */
        "emitDecoratorMetadata": true,                    /* Emit design-type metadata for decorated declarations in source files. */
        "typeRoots": [
        "../JavaScript/typings", "../JavaScript/node_modules/@types"
        ],
        "outDir": "../JavaScript",
        "rootDir": "."
    }
}
```
