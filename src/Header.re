open ReasonReact;

module Styles = {
  open Css;

  let root = style([margin(zero)]);
};

[@react.component]
let make = () => {
  <h1 className=Styles.root> {string("Conway's Game of Life")} </h1>;
};