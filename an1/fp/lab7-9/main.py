from test import Test
from repository.repository import Repository
from controller.service_client import ServiceClient
from controller.service_book import ServiceBook
from controller.service_rental import ServiceRental
from ui.ui import UI

def main():
    """
    functie main care ruleaza tot
    input:  
        ---
    output:
        ---
    return:
        ---
    """

    test = Test()
    test.test()
    repo = Repository()
    service_client = ServiceClient(repo)
    service_book = ServiceBook(repo)
    service_rental = ServiceRental(repo)
    ui = UI(service_client, service_book, service_rental)
    ui.start()

    # 1971215467894

if __name__ == "__main__":
    main()





"""
===================================
+ controller
    - dtos
    - service_book.py
    - service_client.py

+ data
    - clients.txt

+ domain
    + validators
        - book_validator.py
        - client_validator.py
        - rental_validator.py
        - validation_exception.py

    - book.py
    - client.py
    - rental.py

+ repository
    - repository_exception.py
    - repository.py

+ ui
    - ui.py

- main.py
- test.py


====================================


main:
    + test()
    + repo
        - listele
        - load
        - save

        - add
        - check_unique
        - get_all_
        - update
        - delete
    + service_client(repo)
        - add
        - get_all
        - update
        - delete
        
        - save
    + service_book(repo)
        - add
        - get_all
        - update
        - delete
        
        - save
    + service_rental(repo)
        - add
        - get_all
        - update
        - delete
        
        - save
    + ui(service_client, service_book, service_rental)
        - start()
        - read()
        - manage_clients()
        - manage_books()
        - manage_rentals()

"""