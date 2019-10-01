type action =
  | Tick
  | NewGame(int, int);

type gameBoard = array(array(bool));

type gameState = {
  board: gameBoard,
  turn: int,
};

type gameHook = {
  board: gameBoard,
  turn: int,
  tick: unit => unit,
  newGame: unit => unit,
};

Random.init(int_of_float(Js.Date.now()));

let range = (n: int) =>
  Belt.Array.make(n, false)->Belt.Array.mapWithIndex((i, _) => i);

let randomGame = (~width: int, ~height: int) =>
  range(height)
  ->Belt.Array.map(_ => range(width)->Belt.Array.map(_ => false))
  ->Belt.Array.map(row => row->Belt.Array.map(_ => Random.bool()));

let liveNeighbors = (game, i, j) => {
  [
    ((-1), (-1)),
    (0, (-1)),
    (1, (-1)),
    ((-1), 0),
    (1, 0),
    ((-1), 1),
    (0, 1),
    (1, 1),
  ]
  |> List.map(((i2, j2)) => (i + i2, j + j2))
  |> List.map(((i2, j2)) =>
       try (game[i2][j2]) {
       | _ => false
       }
     )
  |> List.filter(cell => cell)
  |> List.length;
};

let gameTick = game => {
  game->Belt.Array.mapWithIndex((i, row) =>
    Belt.Array.mapWithIndex(row, (j, cell) =>
      switch (cell, liveNeighbors(game, i, j)) {
      | (true, 2) => true
      | (true, 3) => true
      | (true, _) => false
      | (false, 3) => true
      | (false, _) => false
      }
    )
  );
};

let gameReducer = (state: gameState, action: action) => {
  switch (action) {
  | Tick => {board: gameTick(state.board), turn: state.turn + 1}
  | NewGame(width, height) => {board: randomGame(~width, ~height), turn: 0}
  };
};

let initialState = (~width: int, ~height: int) => {
  board: randomGame(~width, ~height),
  turn: 0,
};

let useGame = (~width: int, ~height: int): gameHook => {
  let (state, dispatch) =
    React.useReducer(gameReducer, initialState(~width, ~height));

  let tick = React.useCallback1(() => dispatch(Tick), [|dispatch|]);

  let newGame =
    React.useCallback3(
      () => dispatch(NewGame(width, height)),
      (dispatch, width, height),
    );

  {board: state.board, turn: state.turn, tick, newGame};
};