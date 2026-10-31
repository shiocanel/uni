class TicTacToeStatus:
    def __init__(self, game, status, winner):
        self.__data = {
            "game" : game,
            "status" : status,
            "winner" : winner
        }

    def game(self):
        return self.__data["game"]
    def get_status(self):
        return self.__data["status"]
    def get_winner(self):
        return self.__data["winner"]
    def set_game(self, value):
        self.__data["game"] = value
    def set_status(self, value):
        self.__data["status"] = value
    def set_winner(self, value):
        self.__data["winner"] = value
