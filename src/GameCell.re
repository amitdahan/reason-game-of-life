module Styles = {
  open Css;

  let default =
    style([
      transition(
        "background-color",
        ~timingFunction=easeInOut,
        ~duration=100,
      ),
      backgroundColor(black),
      width(px(15)),
      height(px(15)),
      borderRadius(pct(50.)),
    ]);

  let active = style([backgroundColor(green)]);

  let root = live => live ? merge([default, active]) : default;
};

[@react.component]
let make = (~live: bool) => <div className={Styles.root(live)} />;