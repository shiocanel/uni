from domain.TicTacToeGame import TicTacToeGame

class TicTacToeRepository:
    def __init__(self):
        self.__games = []

        self.load_game()

    def load_game(self):
        """
        functie care incarca din fisier jocurile
        input:
            ---
        output:
            ---
        return:
            ---
        """

        with open("D:\\uni\\fp\\sim\\data\\jocuri.txt", "r") as file:
            for line in file:
                parts = line.split(",")
                id, l0c0, l0c1, l0c2, l1c0, l1c1, l1c2, l2c0, l2c1, l2c2 = int(parts[0].strip()), parts[1].strip(), parts[2].strip(), parts[3].strip(), parts[4].strip(), parts[5].strip(), parts[6].strip(), parts[7].strip(), parts[8].strip(), parts[9].strip()

                print(id)
                print("1: ", l0c0)
                print("2: ", l0c1)
                print("3: ", l0c2)
                
                game = TicTacToeGame(id, l0c0, l0c1, l0c2, l1c0, l1c1, l1c2, l2c0, l2c1, l2c2)
                self.__games.append(game)
    
    def getAll(self):
        
        return self.__games
    
    def getById(self, id):
        """
        functie care cauta jocul dupa id
        input:
            - id
        output:
            ---
        return:
            ---
        """
        for game in self.__games:
            if game.get_id() == id:
                return game
            
    def update(self, id, new_game):
        """
        functie care da update si schimba jocul
        input:
            - new_game (TicTacToeGame)
        output:
            ---
        return:
            ---
        """
        
        for game in self.__games:
            if game.get_id() == new_game.get_id():
                game.set_l0c0(new_game.get_l0c0())
                game.set_l0c1(new_game.get_l0c1())
                game.set_l0c2(new_game.get_l0c2())
                
                game.set_l1c0(new_game.get_l1c0())
                game.set_l1c1(new_game.get_l1c1())
                game.set_l1c2(new_game.get_l1c2())
                
                game.set_l2c0(new_game.get_l2c0())
                game.set_l2c1(new_game.get_l2c1())
                game.set_l2c2(new_game.get_l2c2())

                return