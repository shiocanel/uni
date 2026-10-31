    






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
    + client_service(repo)
        - add
        - get_all
        - update
        - delete
    + book_service(repo)
        - add
        - get_all
        - update
        - delete
   
    + rental_service(repo)
        - add
        - get_all
        - update
        - delete

    + ui(client_service, book_service, rental_service)
        - start()
        - read()
        - manage_clients()
        - manage_books()
        - manage_rentals()

"""