module Styles = {
  open Css;

  let root =
    style([
      border(px(1), solid, grey),
      borderRadius(px(10)),
      fontSize(px(24)),
      padding(px(10)),
    ]);
};

[@react.component]
let make = (~onClick: unit => unit, ~children) =>
  <button className=Styles.root onClick={_ => onClick()}> children </button>;