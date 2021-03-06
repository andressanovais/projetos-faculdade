from pylab import *

# -------------------------- BOLSAS -----------------------------

tipos= []
qtds= []

bolsas_file=open("-Bolsas.csv", "r", encoding="utf8")
for line in bolsas_file:
    tipo, qtd = line.strip().split(';') 
    #strip: retira o caracter de new line. split: divide o antes e depois do ponto e virgula
    tipos.append(tipo)
    qtds.append(float(qtd)) 
    # o "float(qtd)" serve para converter a 'qtd' em float, porque ela foi 
    # capturada anteriormente como sendo string

posicoes=arange(len(tipos)) + 0.5 
# arange: cria um vetor contendo uma sequencia de 0 ate um numero definido. 
# nesse caso, essa progressao foi de (0 ate n)+0.5, porque "len" retorna tamanho da array.

bar(posicoes, qtds, align='center', color='#fa5c18')
xticks(posicoes, tipos, rotation=-90, size='xx-small')
plt.title("Quantitativo de bolsas de extensao no campus Uberlandia.")
show()
bolsas_file.close()

# ---------------------------- DOCENTES -----------------------------

cursos= []
numeros= []

docentes_file=open("-Docentes.csv", "r", encoding="utf8")
for line in docentes_file:
    curso, numero= line.strip().split(';')
    cursos.append(curso)
    numeros.append(float(numero))
    
posicoes=arange(len(cursos)) + 0.5

bar(posicoes, numeros, align='center', color='#ffd881')
xticks(posicoes, cursos, rotation=90, size='xx-small')
plt.title("Total de docentes da UNIFEI em 2018.")
show()
docentes_file.close()
    
# ------------------------- SOLDADOS --------------------------------

cursos2= []
valor_total= []

soldados_file=open("-SoldadoCidadao.csv", "r", encoding="utf8")
for line in soldados_file:
    curso2, valor= line.strip().split(';')
    cursos2.append(curso2)
    valor_total.append(float(valor))
    
posicoes=arange(len(cursos2)) + 0.5

bar(posicoes, valor_total, align='center', color='#edd5cd')
xticks(posicoes, cursos2, rotation=90, size='xx-small')
plt.title("Projeto Soldado Cidadao em 2017.")
show()
soldados_file.close()

# ----------------------- MEDICAMENTOS ------------------------------

nomes= []
precos= []

med_file=open("-Medicamentos.csv", "r", encoding="utf8")
for line in med_file:
    nome, preco= line.strip().split(';')
    nomes.append(nome)
    precos.append(float(preco))
    
posicoes=arange(len(nomes)) + 0.5

bar(posicoes, precos, align='center', color='#d97b7a')
xticks(posicoes, nomes, rotation=90, size='xx-small')
plt.title("Precos de Medicamentos.")
show()
med_file.close()

# ---------------------------- PIB ---------------------------------

datas= []
pibs= []

pib_file=open("-PIB.csv", "r", encoding="utf8")
for line in pib_file:
    data, pib= line.strip().split(';')
    datas.append(data)
    pibs.append(float(pib))
    
posicoes=arange(len(datas)) + 0.5

bar(posicoes, pibs, align='center', color='#7189bf')
xticks(posicoes, datas, rotation=90, size='xx-small')
plt.title("Divida Liquida do Setor Publico (% PIB) - Total - Empresas estatais.")
show()
pib_file.close()                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 