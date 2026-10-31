from domain.TicTacToeGame import TicTacToeGame

class TicTacToeService:
    def __init__(self, repo):
        self.__repo = repo

    def getAll(self):
        """
        ifunctie care retunrneaza toate jocurile
        input:
            ---
        output:
            ---
        return:
            ---
        """
        return self.__repo.getAll()

    def searchUnfinishedGames(self):
        """
        ofunctie care cauta jocurile nefinisate
        input:
            ---
        output:
            ---
        return:
            ---
        """

        games = self.__repo.getAll()

        ans = []
        for game in games:
            status = game.get_TicTacToeStatus()
            if status.get_status() == "unfinished":
                ans.append(game)

        return ans
    
    def play(self, id, line, column, player):
        """
        functie care joaca si completeaza un cell
        input:
            - id
            - line
            - column
            - player
        output:
            ---
        return:
            ---
        """

        game = self.__repo.getById(id)

        cell = f"l{line}c{column}"

        if cell == "l0c0": 
            game.set_l0c0(player) 
        elif cell == "l0c1": 
            game.set_l0c1(player)
        elif cell == "l0c2": 
            game.set_l0c2(player)
        elif cell == "l1c0": 
            game.set_l1c0(player)
        elif cell == "l1c1": 
            game.set_l1c1(player) 
        elif cell == "l1c2": 
            game.set_l1c2(player)
        elif cell == "l2c0": 
            game.set_l2c0(player)
        elif cell == "l2c1": 
            game.set_l2c1(player) 
        elif cell == "l2c2": 
            game.set_l2c2(player)

        self.__repo.update(id, game)

    def solve_status(self, game_status):
        """
        functie care verifica daca este terminat sau nu si cine a castigat
        input:
            - game_status
        output:
            ---
        return:
            ---
        """
        if game_status.game.get_l0c0() == game_status.game.get_l0c1() == game_status.game.get_l0c2():
            game_status.set_status("finished")
            game_status.set_winner(game_status.game.get_l1c0())
        if game_status.game.get_l1c0() == game_status.game.get_l1c1() == game_status.game.get_l1c2():
            game_status.set_status("finished")
            game_status.set_winner(game_status.game.get_l1c0())
        if game_status.game.get_l2c0() == game_status.game.get_l2c1() == game_status.game.get_l2c2():
            game_status.set_status("finished")
            game_status.set_winner(game_status.game.get_l2c0())
        if game_status.game.get_l1c0() == game_status.game.get_l1c0() == game_status.game.get_l2c0():
            game_status.set_status("finished")
            game_status.set_winner(game_status.game.get_l1c0())
        if game_status.game.get_l1c1() == game_status.game.get_l1c1() == game_status.game.get_l2c1():
            game_status.set_status("finished")
            game_status.set_winner(game_status.game.get_l1c1())
        if game_status.get_l1c2() == game_status.game.get_l1c2() == game_status.game.get_l2c2():
            game_status.set_status("finished")
            game_status.set_winner(game_status.game.get_l1c2())



        if game_status.game.get_l0c0() == game_status.game.get_l1c1() == game_status.game.get_l2c2():
            game_status.set_status("finished")
            game_status.set_winner(game_status.game.get_l0c0())

        if game_status.game.get_l0c2() == game_status.game.get_l1c1() == game_status.game.get_l2c0():
            game_status.set_status("finished")
            game_status.set_winner(game_status.game.get_l1c1())
