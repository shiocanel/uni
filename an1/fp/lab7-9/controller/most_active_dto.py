class MostActiveDTO:
    def __init__(self, client_name, rental_count):
        self.client_name = client_name
        self.rental_count = rental_count

    def __str__(self):
        return f"{self.client_name} : {self.rental_count}"