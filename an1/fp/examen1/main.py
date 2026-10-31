# from repository.repository import Repository
# from controller.student_service import StudentService
# from controller.subject_service import SubjectService
# from ui.ui import UI

# def main():
#     # test = Test()
#     # test.test()
    
#     repo = Repository()
#     student_service = StudentService(repo)
#     subject_service = SubjectService(repo)
#     ui = UI(student_service, subject_service)
#     ui.start()


# if __name__ == "__main__":
#     main()





































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