open ReasonReact;

module Styles = {
  open Css;

  let root =
    style([
      minHeight(vh(100.)),
      display(flexBox),
      flexDirection(column),
      alignItems(center),
      justifyContent(center),
      backgroundColor(black),
      color(white),
      fontFamily("Verdana"),
    ]);

  global("body", [margin(px(0))]);
};

[@react.component]
let make = () => {
  let width = 40;
  let height = 30;
  let game = GameOfLife.useGame(~width, ~height);
  Hooks.useInterval(game.tick, 500);

  <div className=Styles.root>
    <Header />
    <Game board={game.board} turn={game.turn} />
    <Button onClick={game.tick}> {string("Tick")} </Button>
  </div>;
};