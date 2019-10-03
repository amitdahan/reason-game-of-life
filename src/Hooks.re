open React;

let useInterval = (fn: unit => unit, interval: int) => {
  let cbRef: React.Ref.t(Js.Nullable.t(unit => unit)) =
    useRef(Js.Nullable.null);

  useEffect1(
    () => {
      React.Ref.setCurrent(cbRef, Js.Nullable.return(fn));
      None;
    },
    [|fn|],
  );

  useEffect1(
    () =>
      switch (cbRef->Ref.current->Js.Nullable.toOption) {
      | Some(fn) =>
        let timer = Js.Global.setInterval(fn, interval);
        Some(() => Js.Global.clearInterval(timer));
      | _ => None
      },
    [|interval|],
  );
};