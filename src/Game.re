open ReasonReact;

module Styles = {
  open Css;

  let root =
    style([
      padding(px(20)),
      display(flexBox),
      flexDirection(column),
      alignItems(center),
    ]);

  let grid = (~width: int, ~height: int) =>
    style([
      display(grid),
      gridTemplateRows([`repeat((`num(height), minContent))]),
      gridTemplateColumns([`repeat((`num(width), minContent))]),
      gridGap(px(1)),
    ]);

  let turn = style([marginTop(px(20)), fontSize(px(20))]);
};

[@react.component]
let make = (~board: GameOfLife.gameBoard, ~turn: int) =>
  <div className=Styles.root>
    <div
      className={Styles.grid(
        ~width=Array.length(board[0]),
        ~height=Array.length(board),
      )}>
      {ReasonReact.array(
         board
         ->Belt.Array.mapWithIndex((i, row) =>
             row->Belt.Array.mapWithIndex((j, cell) =>
               <GameCell
                 key={string_of_int(i) ++ "x" ++ string_of_int(j)}
                 live=cell
               />
             )
           )
         ->Belt.Array.concatMany,
       )}
    </div>
    <div className=Styles.turn> {string(string_of_int(turn))} </div>
  </div>;