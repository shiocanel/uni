class BooksNeverRentedDTO:
    def __init__(self, book_id, title):
        self.book_id = book_id
        self.title = title

    def __str__(self):
        return f"ID : {self.book_id} | {self.title}"