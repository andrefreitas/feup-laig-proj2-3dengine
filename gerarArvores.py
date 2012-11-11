def criararvore(x,z,rotacao, num,fich):
    fich.write("<node id=\"Arvore"+str(num)+"\">\n")
    fich.write("    <transforms>\n")
    fich.write("        <translate x=\""+str(x)+"\" y=\"0\" z=\""+str(z)+"\" />\n")
    fich.write("        <rotate axis=\"y\" angle=\""+str(rotacao)+"\" />\n")
    fich.write("    </transforms>\n")
    fich.write("    <appearanceref id=\"inherit\" />\n")
    fich.write("        <children>")
    fich.write("            <noderef id=\"Arvore\" />\n")
    fich.write("        </children>\n")
    fich.write("</node>\n\n")

def criarArvores(comprimento,largura):
    import random
    counter=0
    fo = open("arvores.txt", "w")
    for i in range(largura):
        for j in range(comprimento):
            counter=counter+1
            x=j*3+random.uniform(-2, 4)
            z=i*4+random.uniform(-2, 4)
            rotacao=random.uniform(-20, 30)
            criararvore(x,z,rotacao,counter,fo)
    fo.close()

    f2 = open("arvoreslista.txt", "w")
    for i in range(counter):
        f2.write("<noderef id=\"Arvore"+str(i+1)+"\" />\n")

    f2.close()
          
