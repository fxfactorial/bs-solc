# solc

BuckleScript bindings to
[solc-js](https://github.com/ethereum/solc-js)

Use in your projects with `yarn add bs-solc` and add to your
`"bs-dependencies"`

## Usage

```javascript
let input = "contract x { function g() {} }";

let example_one = () => {
  let output =
    Solc.compile(
      Solc.solc,
      ~compileInput=`sourceCode(input),
      ~optimization=1,
      ()
    );
  Js.Dict.entries(output##contracts)
  |> Array.iter(((key, value)) => {
       let b = value##bytecode;
       Js.log({j|Contract name:$b|j});
     });
};

let example_two = () => {
  let output =
    Solc.compile(
      Solc.solc,
      ~compileInput=
        `collection({
          "sources":
            Js.Dict.fromList([
              (
                "lib.sol",
                "library L { function f() returns (uint) { return 7; } }"
              ),
              (
                "cont.sol",
                "import \"lib.sol\"; contract x { function g() { L.f(); } }"
              )
            ])
        }),
      ~optimization=1,
      ()
    );
  Js.log("Look at these warnings:");
  output##errors |> Array.iter(w => Js.log({j|This warning:$w |j}));
  Js.log("Or how about this bytecode");
  output##contracts
  |> Js.Dict.entries
  |> Array.iter(((key, value)) => {
       let b = value##bytecode;
       Js.log({j|Contract: $key, used bytecode:$b|j});
     });
};

example_one();

example_two();
```

## Improvement:

`linkBytes` could be better typed. I haven't used it yet, hence don't
know its return type.

**NOTE**: Because namespacing is turned off, do not add any more files
to src. All code must be in the single file: `src/solc.re`
