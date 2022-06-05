#include <vector>
#include <iostream>
using namespace std;

template <typename K, typename V>
class Tupla
{
private:
	K chave;
	V valor;
	Tupla *prox;

public:
	Tupla(K c, V v)
	{
		chave = c;
		valor = v;
		prox = NULL;
	}

	K getChave()
	{
		return chave;
	}

	V getValor()
	{
		return valor;
	}

	Tupla *getProx()
	{
		return prox;
	}

	void setProx(Tupla *prox)
	{
		Tupla::prox = prox;
	}
};

template <typename Chave, typename Valor>
class TabelaHash
{

private:
	Tupla<Chave, Valor> **tabela;

	// tamanho atual do array
	int qtde_buckets;
	// qtdade de elementos já inseridos na tabela hash
	int tamanho;

	/**
	 * Função para inserir a tupla <c,v> na tabela.
	 * É preciso calcular o código hash a partir da chave c.
	 * Em seguida, usamos qtde_buckets para descobrir o índice
	 * dessa tupla. Prestar atenção na alocação de tupla quando
	 * há colisões. A função hash às vezes retorna valores
	 * negativos: use abs() para evitar índices negativos.
	 **/
	void inserir(Chave c, Valor v, Tupla<Chave, Valor> **tabela)
	{
		// IMPLEMENTAR
		Tupla<Chave, Valor> *t = new Tupla<Chave, Valor>(c, v);

		int id = hash<string>{}(c);
		id = abs(id);
		id = id % qtde_buckets;

		if (tabela[id] == 0)
		{
			tabela[id] = t;
		}
		else
		{
			Tupla<Chave, Valor> *top = tabela[id];
			while (top->getProx() != NULL)
			{
				if (top->getChave() == c)
					return;
				top = top->getProx();
			}
			top->setProx(t);
		}
	}

	/**
	 * Função para aumentar o tamanho do array quando o
	 * fator de carga for >= 1. O tamanho do array
	 * (qtde_buckets) deve ser multiplicado por 8 para
	 * que essa operação seja feita com pouca frequência.
	 * Por fim, precisamos reposicionar as tuplas, considerando
	 * que a posição nesse novo array com maior tamanho
	 * será diferente.
	 **/
	void aumentaArray()
	{
		// IMPLEMENTAR
		if (load_factor() < 1.0)
			return;

		int antigo_qtde_buckets = qtde_buckets;
		qtde_buckets *= 8;
		Tupla<Chave, Valor> **nova_tabela = (Tupla<Chave, Valor> **)calloc(qtde_buckets, sizeof(Tupla<Chave, Valor> *));

		for (int i = 0; i < antigo_qtde_buckets; i++)
		{
			if (tabela[i] != 0)
			{
				Tupla<Chave, Valor> *top = tabela[i];
				while (top != NULL)
				{
					inserir(top->getChave(), top->getValor(), nova_tabela);
					top = top->getProx();
				}
			}
		}

		delete[] tabela;
		tabela = nova_tabela;
	}

public:
	/**
	 * Inicializar o array de tuplas com capacidade = qtde_buckets.
	 * Lembrar de setar todas as posições do array inicializado
	 * para NULL.
	 **/
	TabelaHash()
	{
		// IMPLEMENTAR
		tabela = (Tupla<Chave, Valor> **)calloc(8, sizeof(Tupla<Chave, Valor> *));
		qtde_buckets = 8;
		tamanho = 0;
	}

	/**
	 * Essa é a função pública que nos permite inserir
	 * uma tupla <c,v> na tabela. Nessa função nós
	 * verificamos se é preciso aumentar o array de acordo
	 * com o load factor. Essa função pode reusar sua versão
	 * sobrecarregada para inserir a tupla na tabela.
	 * Essa função também incrementa a quantidade de elementos
	 * na tabela (variável tamanho).
	 **/
	void inserir(Chave c, Valor v)
	{
		// IMPLEMENTAR
		if (load_factor() >= 1.0)
			aumentaArray();
		inserir(c, v, tabela);
		tamanho++;
	}

	/**
	 * Essa função retorna o fator de carga da Tabela Hash.
	 **/
	double load_factor()
	{
		// IMPLEMENTAR
		return (double)(tamanho) / (double)(qtde_buckets);
	}

	/**
	 * Há apenas um valor associado a uma chave.
	 * Essa função retorna esse valor, caso a chave exista.
	 * Se a chave não existir a função retorna NULL.
	 * Lembre-se: em caso de colisão, é preciso navegar
	 * no bucket (lista ligada) para ter certeza se a chave
	 * existe ou não.
	 **/
	Valor getValor(Chave chave)
	{
		// IMPLEMENTAR
		int id = hash<string>{}(chave);
		id = abs(id);
		id = id % qtde_buckets;

		if (tabela[id] != 0)
		{
			Tupla<Chave, Valor> *top = tabela[id];
			while (top->getChave() != chave)
			{
				if (top->getProx() == NULL)
					return 0;
				top = top->getProx();
			}
			return top->getValor();
		}
		return 0;
	}

	/**
	 * Essa função retorna true caso a chave exista,
	 * false caso contrário.
	 * Lembre-se: em caso de colisão, é preciso navegar
	 * no bucket (lista ligada) para ter certeza se a chave
	 * existe ou não.
	 **/
	bool contemChave(Chave chave)
	{
		// IMPLEMENTAR
		int id = hash<string>{}(chave);
		id = abs(id);
		id = id % qtde_buckets;

		if (tabela[id] != 0)
		{
			Tupla<Chave, Valor> *top = tabela[id];
			while (top->getChave() != chave)
			{
				if (top->getProx() == NULL)
					return false;
				top = top->getProx();
			}
			return true;
		}
		return false;
	}

	/**
	 * Essa função retorna um vetor com todas as chaves
	 * já inseridas na tabela.
	 **/
	vector<Chave> getChaves()
	{
		// IMPLEMENTAR
		vector<Chave> chaves;
		for (int i = 0; i < qtde_buckets; i++)
		{
			if (tabela[i] != 0)
			{
				Tupla<Chave, Valor> *top = tabela[i];
				while (top != NULL)
				{
					chaves.push_back(top->getChave());
					top = top->getProx();
				}
			}
		}

		return chaves;
	}

	/**
	 * Essa função desaloca os nós previamente alocados, e muda
	 * o tamanho do array de tuplas para 8.
	 **/
	void clear()
	{
		// IMPLEMENTAR
		for (int i = 0; i < qtde_buckets; i++)
		{
			Tupla<Chave, Valor> *top = tabela[i];
			while (top != NULL)
			{
				Tupla<Chave, Valor> *temp = top;
				top = top->getProx();
				delete temp;
			}
			tabela[i] = 0;
		}

		delete[] tabela;
		qtde_buckets = 8;
		tamanho = 0;
	}

	/**
	 * Há apenas um nó associado com uma mesma chave.
	 * Essa função remove esse nó da tabela, caso a chave exista.
	 * Se a chave não existir a função não faz nada.
	 * Lembre-se: em caso de colisão, é preciso navegar
	 * no bucket (lista ligada) para ter certeza se a chave
	 * existe ou não.
	 * Dica: olhar algoritmo de remoção em lista ligada, pois
	 * após a remoção de um nó a lista precisa permanecer íntegra,
	 * ou seja, navegável.
	 **/
	void remover(Chave chave)
	{
		// IMPLEMENTAR
		int id = hash<string>{}(chave);
		id = abs(id);
		id = id % qtde_buckets;

		if (tabela[id] != 0)
		{
			Tupla<Chave, Valor> *top = tabela[id];
			Tupla<Chave, Valor> *anterior = NULL;

			while (top->getChave() != chave)
			{
				anterior = top;
				top->getProx();

				if (top == NULL)
					return;
			}

			if (anterior == NULL)
			{
				tabela[id] = top->getProx();
			}
			else
			{
				anterior->setProx(top->getProx());
			}

			tamanho--;
			delete top;
		}
	}

	/**
	 * Essa função retorna a quantidade de pares
	 * que já foram inseridos na Tabela Hash.
	 **/
	int size()
	{
		return tamanho;
	}

	/**
	 * Essa função retorna o tamanho atual do
	 * array usado para armazenar a Tabela Hash.
	 **/
	int bucket_count()
	{
		return qtde_buckets;
	}
};
