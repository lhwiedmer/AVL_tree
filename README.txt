Implementação da Árvore AVL

Luiz Henrique Murback Wiedmer – GRR20221234
Eduardo Giehl - GRR20221222

1. Estruturas de Dados
Nenhuma estrutura foi utilizada para representar a árvore em si, ao invés disso foi utilizada apenas uma estrutura para representar um nodo da árvore. Ela possui dois inteiros, um para representar a chave do nodo, e o outro para representar o balanço(altura da subárvore esquerda – altura da subárvore direita) dele. Além disso possui três ponteiros para a mesma estrutura, um que aponta para o pai, e os outros dois para os filhos esquerdo e direito.

2. Funções

2.1. Inserir
A função recebe um ponteiro para um ponteiro para nodo(que deve representar a raiz da árvore) e a chave inteira que deve ser inserida.
Ela cria um nodo com a chave a ser inserida e, caso a chave não esteja presente na árvore(se ela já estiver destrói o nodo criado e retorna NULL), insere o nodo seguindo as regras de uma árvore de busca binária.
Se o nodo inserido foi a raiz, a função apenas retorna um ponteiro para o nodo após o inserir. Caso não seja a raiz, ele atualiza o balanço da árvore a partir do nodo inserido, e caso o balanço de um nodo seja 2 ou -2, corrige a árvore utilizando rotações a partir do nodo com balanço errado. Ao final do processo retorna o nodo inserido.

2.2. Buscar
A função recebe um ponteiro para nodo(que deve representar a raiz) e a chave a ser buscada. A busca é feita de maneira recursiva, comparando a chave buscada com a do nodo atual, fazendo a chamada recursiva para o filho direito caso a chave buscada seja maior que a atual, e filho direito para caso seja menor. A função retorna quando chega na chave certa ou em um nodo nulo(nesse caso retorna NULL porque a chave não existe na árvore).

2.3. Excluir
A função recebe um ponteiro para um ponteiro para nodo(que deve representar a raiz da árvore) e a chave inteira que deve ser excluída.
A função primeiramente busca o nodo a ser excluído e, caso a chave não esteja presente na árvore, retorna 0. Existem 3 possíveis casos para a remoção do nodo.

2.3.1. Sem filhos
O primeiro caso é quando o nodo não tem filhos, nessa situação é apenas necessário atualizar o balanço de seu pai(se ele existir), ajustar os ponteiros, e apagar o nodo da memória. 

2.3.2 e 2.3.3. Um filho
O segundo caso e o terceiro caso são espelhados, e ocorrem caso o nodo tenha apenas um filho, nessa situação é necessário atualizar o balanço do pai assim como no caso 1, e, antes de apagar o nodo, é preciso fazer com que seu pai se transforme no pai do seu filho, e então apagá-lo da memória. 

2.3.4. Dois filhos
O quarto caso ocorre quando o nodo tem filhos esquerdo e direito. Nessa situação é necessário encontrar o nodo antecessor(o nodo mais a direita da subárvore esquerda) e trocar as posição dele com a do nodo a ser retirado, e então apagar o nodo intencionado como se fosse um nodo sem filhos(2.3.1) ou com um filho esquerdo(2.3.2). Caso o antecessor seja o filho esquerdo, não é necessário colocar o nodo a ser excluído no lugar do antecessor, apenas excluí-lo após colocar o antecessor em seu lugar.

2.3.5. Atualização e correção
Caso o nodo a ser removido fosse uma raiz com um ou zero filhos, a função apenas retorna 1 sem atualizar o balanço da árvore ou fazer correções, já que elas não seriam necessárias. Em qualquer outro caso o balanço da árvore é atualizado a partir do pai do nodo removido, sendo que a atualização ocorre até que se encontre um nodo com o balanço 1 ou -1, o que significa que a árvore já está balanceada, ou até que se encontre a raiz(o balanço dela não pode ser 2 ou -2), ou caso seja encontrado um nodo com balanço 2 ou -2, o que significa que aquele nodo precisa de correção. Após a correção é necessário verificar se o balanço do nodo que terminou como a base da rotação é 0(a menos que ele fosse raiz), porque  se ele for, é necessário continuar o processo de atualização e possível correção descrito antes. Ao final do processo a árvore estará balanceada e a função retornará 1.

2.4. Imprimir em ordem
A função recebe um ponteiro para nodo(que deve representar a raiz da árvore) e imprime a árvore de maneira ordenada a partir desse nodo.

2.5. Imprimir em largura
A função recebe um ponteiro para nodo(que deve representar a raiz da árvore) e imprime a árvore por nível, partindo da raiz e descendo até as folhas. Para isso é utilizada uma fila(implementada no arquivo libfila.c com os headers presentes no arquivo libfila.h) além de três contadores, o primeiro define o nível atual, o segundo controla quantos nodos do nível atual ainda estão na fila, e o terceiro que serve como acumulador para guardar o número de nodos do proximo nível, valor que posteriormente, quando o primeiro contador aumentar, será passado para o segundo contador.

2.6. Destrói árvore
A função recebe um ponteiro para nodo(que deve representar a raiz da árvore) e libera a memória da árvore a partir desse nodo, seguindo um percurso pós ordem.
