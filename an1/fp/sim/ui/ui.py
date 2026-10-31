class UI:
    def __init__(self, service):
        self.__service = service

    def read(self, text, expected_type):
        """
        functie care citeste un anumit tip 
        input:
            - text (string) pentru uitilizator
            - expected_type (type) tipul de date asteptat de utilizator
        ouptut:
            ---
        return:
            - data (expected_type)
        """
        while True:
            try:
                data = input(text)
                data = expected_type(data)
                return data
            except ValueError:
                print("Nu e bine!!!")    

    def start(self):
        """
        functie de ui care face interfata
        input:
            ---
        output:
            ---
        retur:
            ---
        """

        while True:
            print("\n\n")
            print("==MENU==")
            print("1) All Games")
            print("2) Search Unfinished Games")
            print("3) Play")
            print("0) Exit")
            option = self.read("Option: ", str)
            print("\n\n")

            if option == "1":
                games = self.__service.getAll()
    
                print("==All Games==")
                for game in games:
                    print()
                    print("id: ", game.get_id())
                    print(f"{game.get_l0c0()} | {game.get_l0c1()} | {game.get_l0c2()}")
                    print(f"__________")
                    print(f"{game.get_l1c0()} | {game.get_l1c1()} | {game.get_l1c2()}")
                    print(f"__________")
                    print(f"{game.get_l2c0()} | {game.get_l2c1()} | {game.get_l2c2()}")
                    print()

                    # self.__service.solve_status(game.get_TicTacToeStatus())
                    # am bug
                    status = game.get_TicTacToeStatus()

                    print(f"Status: {status.get_status()}")
                    print(f"Winner: {status.get_winner()}")
                    print()
            elif option == "2":
                games = self.__service.searchUnfinishedGames()
    
                print("==Unfinished Games==")
                for game in games:
                    print()
                    print("id: ", game.get_id())
                    print(f"{game.get_l0c0()} | {game.get_l0c1()} | {game.get_l0c2()}")
                    print(f"__________")
                    print(f"{game.get_l1c0()} | {game.get_l1c1()} | {game.get_l1c2()}")
                    print(f"__________")
                    print(f"{game.get_l2c0()} | {game.get_l2c1()} | {game.get_l2c2()}")
                    print()
            elif option == "3":
                id = self.read("id: ", int)
                line = self.read("line: ", int)
                column = self.read("column: ", int)
                player = self.read("player: ", str)

                self.__service.play(id, line, column, player)

                print("==Game played successfully==")
            elif option == "0":
                print("Sa fie cu bine!!")
                return
            else:
                print("Invalid Option!!!")
            



