type t = {
  .
  "supportsMulti": Js.boolean,
  "supportsImportCallback": Js.boolean,
  "supportsStandard": Js.boolean
};

[@bs.module] [@bs.val] external solc : t = "";

[@bs.send] external version : t => string = "";

type readCb =
  string =>
  {
    .
    "error": Js.Undefined.t(string),
    "contents": string
  };

type contract = {
  .
  "assembly": {
    .
    /* ".data" is missing */
    "code":
      array(
        {
          .
          "begin": int,
          "end": int,
          "name": string,
          "value": string
        }
      )
  },
  "bytecode": string,
  "functionHashes": Js.Dict.t(string),
  "gasEstimates": {
    .
    "creation": array(int),
    "external": Js.Dict.t(int),
    "internal": Js.Dict.t(int)
  },
  "interface": string,
  "metadata": string,
  "opcodes": string,
  "runtimeBytecode": string,
  "srcmap": string,
  "srcmapRuntime": string
};

type node = {
  .
  "attributes": {
    .
    "absolutePath": string,
    "exportedSymbols": Js.Dict.t(array(int))
  },
  "children": Js.Undefined.t(array(node)),
  "id": int,
  "name": string,
  "src": string
};

type compileResult = {
  .
  "contracts": Js.Dict.t(contract),
  "errors": array(string),
  "sources": Js.Dict.t({. "AST": node}),
  "sourceList": array(string)
};

[@bs.send]
external compile :
  (
    t,
    ~compileInput: [@bs.unwrap]
                   [
                     | `collection({. "sources": Js.Dict.t(string)})
                     | `sourceCode(string)
                   ],
    ~optimization: int,
    ~readCb: Js.Undefined.t(readCb)=?,
    unit
  ) =>
  compileResult =
  "";

[@bs.send] external license : t => string = "";

[@bs.send] external compileStandardWrapper : t => compileResult = "";

[@bs.send] external linkBytecode : (t, string, Js.Dict.t(string)) => 'a = "";
