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

type compileResult('contracts) = {
  .
  "contracts": Js.Dict.t(Js.t({..}) as 'contracts),
  "errors": array(string),
  "sources": string,
  "sourceList": array(string)
};

[@bs.send]
external compile :
  (
    t,
    ~compileInput: [@bs.unwrap]
                   [ | `collection(Js.Dict.t(string)) | `sourceCode(string)],
    ~optimization: int,
    ~readCb: Js.Undefined.t(readCb),
    unit
  ) =>
  compileResult(Js.t({..})) =
  "";

[@bs.send] external license : t => string = "";

[@bs.send]
external compileStandardWrapper : t => compileResult(Js.t({..})) = "";

[@bs.send] external linkBytecode : (t, string, Js.Dict.t(string)) => 'a = "";
