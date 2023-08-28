#Luiz Alonso Bispo Poubel Curso: Big Data e Inteligencia Analitica EAD
import json

nomes = ["Alunos", "Professores", "Diciplinas", "Turmas", "Matriculas"]
#escola = [[], [], [], [], []]
escola = [[], [], [], [], []]
estado = 0
estado_lista = escola[0]
estado_nome = "aaaa"
Savefile = "escola.json"


def salvar():
    with open(Savefile, "w") as f:
        objeto_json = json.dump(escola, f)


def recuperar():
    global escola
    try:
        with open(Savefile, "r") as f:
            escola = json.load(f)
    except:
        escola = [[], [], [], [], []]


def Listar():
    if len(estado_lista) == 0:
        print ("Não há cadastros de", estado_nome)
    else:
        print(estado_nome, " cadastrados:")
        for cadastro in estado_lista:
            print(cadastro)

def incluir():
    print("-----INCLUSÃO-----")
    cadastro = {}
    if estado == 0 or estado == 1: # Estudante & Professor
        cadastro.update({"codigo": int(input("Insira o codigo do " + estado_nome))})
        cadastro.update({"nome": str(input("Insira o nome do " + estado_nome))})
        cadastro.update({"cpf": input("Insira o cpf do " + estado_nome)})
    elif estado == 2: # Diciplina
        cadastro.update({"codigo": int(input("Insira o codigo da diciplina"))})
        cadastro.update({"nome": str(input("Insira o nome da diciplina"))})
    elif estado == 3: # Turma
        # TODO Verificação da existencia de codigos
        cadastro.update({"codigo": int(input("Insira o codigo da turma")) })
        cadastro.update({"codigo_professor": int(input("Insira o codigo da professor"))})
        cadastro.update({"codigo_diciplina": int(input("Insira o codigo da diciplina"))})
    elif estado == 4: # Matricula
        # TODO Verificação da existencia de codigos
        cadastro.update({"codigo": int(input("Insira o codigo da matricula"))})
        codigo_turma = int(input("Insira o codigo da turma"))
        if verificar(codigo_turma, escola[3]):
            cadastro.update({"codigo_turma":  codigo_turma})
        cadastro.update({"codigo_estudante": int(input("Insira o codigo da estudante"))})

    estado_lista.append(cadastro)
    print(estado_nome, " adicionado com sucesso!")


def editar ():
    print ("-----EDITAR-----")
    codigo = int(input("Digite o codigo de " + estado_nome))
    for cadastro in estado_lista:
        if cadastro["codigo"] == codigo:
            estado_lista.remove(cadastro)
            estado_lista.append(incluir())
            return
    print (estado_nome, " de codigo:", codigo, "nao existe.")

def verificar(codigo, lista):
    for cadastro in lista:
        if cadastro["codigo"] == codigo:
            return True
    return False

def excluir ():
    print ("-----EXCLUIR-----")
    codigo = int(input("Digite o codigo de " + estado_nome))
    for cadastro in estado_lista:
        if cadastro["codigo"] == codigo:
            print(estado_nome, "removido com sucesso")
            estado_lista.remove(cadastro)
            return
    print (estado_nome, " de codigo:", codigo, "nao existe.")

def menudeoperações():
    while True:
        print("estado_nome:", estado_nome)
        print("\t-------Menu ", estado_nome,"-------\n")
        print("(1) listar\n")
        print("(2) incluir\n")
        print("(3) excluir\n")
        print("(4) editar\n")
        print("(5) Sair\n")
        y = int(input("escolha umas das opcões"))
        if y < 1 or y > 5 :
          print("Porvafor Insira uma Opção valida.")
          continue
        if y == 1:
            Listar()
        elif y == 2:
            incluir()
        elif y == 3:
            excluir()
        elif y == 4:
            editar()
        elif y == 5:
            break
        salvar()

def main():
    recuperar()
    global estado
    global estado_nome
    global estado_lista
    while True:
        print("\t----Menu Inicial----")
        print("(1) Estudantes")
        print("(2) Professores")
        print("(3) Disciplinas")
        print("(4) Turmas")
        print("(5) Matrículas")
        x = int(input("escolha umas das opcões: "))
        if x < 1 or  x > 5:
            print("Porvafor Insira uma Opção valida.")
            continue
        estado = x - 1
        estado_nome = nomes[estado]
        estado_lista = escola[estado]
        print("estado:", estado)
        print("estado_nome:", estado_nome)
        print("estado_lista:", estado_lista)
        menudeoperações()

#salvar()
main()
