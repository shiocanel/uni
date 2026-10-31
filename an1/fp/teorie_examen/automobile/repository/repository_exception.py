class RepositoryException(Exception):
    def __init__(self, msg):
        self.__msg = msg

    def get_message(self):
        return self.__msg