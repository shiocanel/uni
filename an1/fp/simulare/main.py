from test import Test
from repository.repository import Repository
from controller.service_client import ServiceClient
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
    ui = UI(service_client)
    ui.start()

    # 1971215467894

if __name__ == "__main__":
    main()


"""
deci cum facem la simulare

controller:
    -service_client.py
data:
    -clients.txt
domain:
    validators:
        -client_validator.py
        -validation_exception.py

    -client.py
repository:
    -repository_exception.py
    -repository.py
ui:
    -ui.py
-main.py
-test.py



le luam pe rand
1) facem toate folderele si fisierele
2) facem mainu
3) clients.txt

4) client.py
5) validation_exception.py
6) client_validator.py
7) service_client.py (add update delete see_all save) saveu ultimu dalan mortii lui

8) repository_exception.py (exact ca si validation_exception)
9) repository.py

10) ui

11) test
"""