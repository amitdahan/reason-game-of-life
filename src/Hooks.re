open React;

let useInterval = (fn: unit => unit, interval: int) => {
  useEffect2(
    () => {
      let timer = Js.Global.setInterval(fn, interval);
      Some(() => Js.Global.clearInterval(timer));
    },
    (fn, interval),
  );
};