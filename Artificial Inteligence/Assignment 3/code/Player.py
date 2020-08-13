import numpy as np

MAX_DEPTH = 100

class AIPlayer:
    def __init__(self, player_number):
        self.player_number = player_number
        self.type = 'ai'
        self.player_string = 'Player {}:ai'.format(player_number)
        self.depth = 0

    def get_alpha_beta_move(self, board):
        """
        Given the current state of the board, return the next move based on
        the alpha-beta pruning algorithm

        This will play against either itself or a human player

        INPUTS:
        board - a numpy array containing the state of the board using the
                following encoding:
                - the board maintains its same two dimensions
                    - row 0 is the top of the board and so is
                      the last row filled
                - spaces that are unoccupied are marked as 0
                - spaces that are occupied by player 1 have a 1 in them
                - spaces that are occupied by player 2 have a 2 in them

        RETURNS:
        The 0 based index of the column that represents the next move
        """
        array = self.valid_column(board)
        v = self.value(board, -999999, 999999)
        move = self.value_to_col(board, v, True)
        prev = move
        move = self.lose_check(board, move)
        if move in array:
          return move
        else:
          move = prev
          return move
        

        raise NotImplementedError('Whoops I don\'t know what to do')

    def value(self, board, a, b):
        if self.depth == MAX_DEPTH:
           return self.evaluation_function(board)
        else:
            if self.depth%2 == 0:
                return self.max_value(board, a, b)
            else:
                return self.min_value(board, a, b)

    def max_value(self, board, a ,b):
        v = -999999
        cols = self.valid_column(board)
        temp_board = board
        self.depth += 1
        for col in cols:
            self.set(board, col)
            v = max(v, self.value(board, a, b))
            if v >= b:
                board = temp_board
                return v
            a = max(a, v)
            board = temp_board
        return v

    def min_value(self, board, a ,b):
        v = 999999
        cols = self.valid_column(board)
        temp_board = board
        self.depth += 1
        for col in cols:
            self.set(board, col)
            v = min(v, self.value(board, a, b))
            if v <= a:
                board = temp_board
                return v
            b = min(b, v)
            board = temp_board
        return v

    def valuee(self, board):
        if self.depth == MAX_DEPTH:
           return self.evaluation_function(board)
        else:
            if self.depth%2 == 0:
                return self.max_valuee(board)
            else:
                return self.exp_value(board)

    def max_valuee(self, board):
        v = -999999
        cols = self.valid_column(board)
        temp_board = board
        self.depth += 1
        for col in cols:
            self.set(board, col)
            v = max(v, self.valuee(board))
            board = temp_board
        return v

    def exp_value(self, board):
        v = 0
        cols = self.valid_column(board)
        temp_board = board
        p = 1/len(cols)
        self.depth += 1
        for col in cols:
            self.set(board, col)
            v += p * self.valuee(board)
            board = temp_board
        return v

    def valid_column(self, board):
        valid_cols = []
        for i, col in enumerate(board.T):
            if 0 in col:
                valid_cols.append(i)
        return valid_cols

    def set(self, board, col):
      array = board[:][col-1]
      for p in range(6):
        if array[p] != 0:
          board[p+1][col] = self.player_number
          return
        

    def value_to_col(self, board, v, bool):
        cols = self.valid_column(board)
        if bool == True:
            for i in cols:
                if self.value(board, -999999, 999999) == v:
                    return i
        else:
            for i in cols:
                if self.valuee(board) == v:
                    return i
    
    def lose_check(self, board, move):
      count = 0;
      num = 0
      if self.player_number == 1:
        n = 2
      else:
        n = 1
      
      for i, row in enumerate(board):
          for p in range(3):
              if row[p] == n:
                for j in range(1, 5):
                  if row[p+j] == n:
                    count += 1
                  elif row[p+j] == 0:
                    num = p+j
                  elif row[p+j] == self.player_number:
                    break
                  if count == 2:
                    return num
        
      num = 0
      for i in range(7):
        for p in range(4):
            if board[p][i] == n:
              if board[p+1][i] == n and board[p+2][i] == n:
                return i
      return move
                
    
    def utility_add(self, count, utility):
      if count == 1:
          utility += 1
      elif count == 2:
          utility += 10
      elif count == 3:
          utility += 100
      elif count == 4:
          utility += 1000
      return utility
      

    def get_expectimax_move(self, board):
        """
        Given the current state of the board, return the next move based on
        the expectimax algorithm.

        This will play against the random player, who chooses any valid move
        with equal probability

        INPUTS:
        board - a numpy array containing the state of the board using the
                following encoding:
                - the board maintains its same two dimensions
                    - row 0 is the top of the board and so is
                      the last row filled
                - spaces that are unoccupied are marked as 0
                - spaces that are occupied by player 1 have a 1 in them
                - spaces that are occupied by player 2 have a 2 in them

        RETURNS:
        The 0 based index of the column that represents the next move
        """
        array = self.valid_column(board)
        v = self.valuee(board)
        move = self.value_to_col(board, v, False)
        prev = move
        move = self.lose_check(board, move)
        if move in array:
          return move
        else:
          move = prev
          return move

        raise NotImplementedError('Whoops I don\'t know what to do')




    def evaluation_function(self, board):
        """
        Given the current stat of the board, return the scalar value that
        represents the evaluation function for the current player
       
        INPUTS:
        board - a numpy array containing the state of the board using the
                following encoding:
                - the board maintains its same two dimensions
                    - row 0 is the top of the board and so is
                      the last row filled
                - spaces that are unoccupied are marked as 0
                - spaces that are occupied by player 1 have a 1 in them
                - spaces that are occupied by player 2 have a 2 in them

        RETURNS:
        The utility value for the current board
        """
        utility = 0
        count = 0
        switch = False
        
        #calculating utility scores in rows
        for i, row in enumerate(board):
            for p in range(7):
                if row[p] == self.player_number:
                    switch = True
                else:
                    switch = False

                if switch == True:
                    count += 1
                    if count == 5:
                        utility += 1001
                        count = 0
                else:
                  utility = self.utility_add(count, utility)
                  count = 0
        utility = self.utility_add(count, utility)
        count = 0
        switch = False
        # calculating utility scores in columns
        for i in range(7):
            for p in range(6):
                if board[p][i] == self.player_number:
                    switch = True
                else:
                    switch = False

                if switch == True:
                    count += 1
                    if count == 5:
                        utility += 1001
                        count = 0
                else:
                    utility = self.utility_add(count, utility)
                    count = 0
        utility = self.utility_add(count, utility)
        count = 0
        switch = False

        #calculating utility scores in diagonals
        root_diag = np.diagonal(board, offset=0).astype(np.uint8)
        for p in range(len(root_diag)):
            if root_diag[p] == self.player_number:
                switch = True
            else:
                switch = False
            if switch == True:
                count += 1
                if count == 5:
                    utility += 1001
                    count = 0
            else:
                utility = self.utility_add(count, utility)
                count = 0
        utility = self.utility_add(count, utility)
        count = 0
        switch = False

        for i in range(1, board.shape[1] - 3):
            for offset in [i, -i]:
                diag = np.diagonal(board, offset=offset).astype(np.uint8)
                for p in range(len(diag)):
                    if diag[p] == self.player_number:
                        switch = True
                    else:
                        switch = False
                    if switch == True:
                        count += 1
                        if count == 5:
                            utility += 1001
                            count = 0
                    else:
                        utility = self.utility_add(count, utility)
                        count = 0
        utility = self.utility_add(count, utility)
        return utility


class RandomPlayer:
    def __init__(self, player_number):
        self.player_number = player_number
        self.type = 'random'
        self.player_string = 'Player {}:random'.format(player_number)

    def get_move(self, board):
        """
        Given the current board state select a random column from the available
        valid moves.

        INPUTS:
        board - a numpy array containing the state of the board using the
                following encoding:
                - the board maintains its same two dimensions
                    - row 0 is the top of the board and so is
                      the last row filled
                - spaces that are unoccupied are marked as 0
                - spaces that are occupied by player 1 have a 1 in them
                - spaces that are occupied by player 2 have a 2 in them

        RETURNS:
        The 0 based index of the column that represents the next move
        """
        valid_cols = []
        for col in range(board.shape[1]):
            if 0 in board[:,col]:
                valid_cols.append(col)

        return np.random.choice(valid_cols)


class HumanPlayer:
    def __init__(self, player_number):
        self.player_number = player_number
        self.type = 'human'
        self.player_string = 'Player {}:human'.format(player_number)

    def get_move(self, board):
        """
        Given the current board state returns the human input for next move

        INPUTS:
        board - a numpy array containing the state of the board using the
                following encoding:
                - the board maintains its same two dimensions
                    - row 0 is the top of the board and so is
                      the last row filled
                - spaces that are unoccupied are marked as 0
                - spaces that are occupied by player 1 have a 1 in them
                - spaces that are occupied by player 2 have a 2 in them

        RETURNS:
        The 0 based index of the column that represents the next move
        """

        valid_cols = []
        for i, col in enumerate(board.T):
            if 0 in col:
                valid_cols.append(i)

        move = int(input('Enter your move: '))

        while move not in valid_cols:
            print('Column full, choose from:{}'.format(valid_cols))
            move = int(input('Enter your move: '))

        return move

