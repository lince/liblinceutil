/*Nota.
 Esta classe não foi desenvolvida por nós. Apenas a adaptamos para utilizar no miniprojeto.
 
 A versão original desta classe pode ser encontrada em:
 http://svn.softwarepublico.gov.br/trac/ginga/browser/telemidia-util-cpp/trunk/include/Thread.h
 http://svn.softwarepublico.gov.br/trac/ginga/browser/telemidia-util-cpp/trunk/src/Thread.cpp
 
 É necessário se cadastrar no site http://www.softwarepublico.gov.br/ para ter acesso ao svn.
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <errno.h>
#include <sys/time.h>
#include <pthread.h>

namespace cpputil {
//! Classe virtual pura que representa uma Thread.
/*! Esta classe tem um comportamento semelhante a classe Thread da linguagem Java.
 * Qualquer classe que deseje ser uma Thread deve extender esta classe e sobreescrever
 * o método run, inserindo neste a função de entrada do novo Thread que será utilizado.
 * O novo thread iniciará sua execução quando o método start for evocado.
 */
  class Thread {
	protected:
		//! variável que armazena a thread de mutex
		pthread_mutex_t threadMutex;
		
		//! variável que armazena a condição da thread de "está dormindo"
		bool isSleeping;
		
		//! variável que armazena a flag de mutex
		pthread_mutex_t threadFlagMutex;
		
		//! pthread que armazena a flag de condição 
		pthread_cond_t threadFlagConditionVariable;
		
		//! variável que armazena a condição da thread de "está esperando"
		bool isWaiting;
		
		//! variável que armazena a thread flag de trancamento até ser dado um sinaal
		pthread_mutex_t threadFlagMutexLockUntilSignal;
		
		//! pthread que armazena a flag de condição de trancamento até ser dado um sinaal
		pthread_cond_t threadFlagCVLockUntilSignal;

		//! método virtual que executa a thread
		virtual void run() = 0;

	private:
		//! armazena a ID da thread
		pthread_t threadId_;
		
		//! Utilizada pela blibioteca pthreads para iniciar.
		/*! A biblioteca pthreads faz com que as threads tenham seus pontos de entrada
		 * uma função que retorna um ponteiro para void e tem como parametro outro ponteiro para void.
		 * Este método estático da classe é esta função. 
		 * Ela é evocada pelo método start que passa como parametro a instância que implementa thread
		 * para qual start foi evocada, esta função então chama o método run desta instância.
		 */
		static void* function(void* ptr);

	public:
		//! contrutor padrão
		/*!
			inicializa:
			variáveis tipo bool: isSleeping; isWaiting;
			thread mutex type: threadMutex; threadFlagMutex; threadFlagMutexLockUntilSignal;
			thread conditional variable type: threadFlagConditionVariable; threadFlagCVLockUntilSignal;
		*/
		Thread();
		
		//! destrutor
		/*!
			destrói todas as pthread's
		*/
		virtual ~Thread();
		
		//! Inicia a execução da Thread
		virtual void start();
		
		//! Faz a thread por alguns segundos.
		/*!
			\param seconds tempo em segundos que a Thread deve durmir.
		*/
		bool sleep(long int seconds);
		
		//! Faz a thread por alguns milissegundos
		/*!
		 	\param milliseconds tempo em milissegundos que a Thread deve durmir
		 */
		bool usleep(long int milliseconds);
		
		//! libera pthread de condição
		/*!
			se tiver dormindo então libera a pthread de condição threadFlagConditionVariable.
		*/
		void wakeUp();
		
		//! tranca a pthread
		/*!
			tranca a pthread threadMutex.
		*/
		void lock();
		
		//! destranca a pthread
		/*!
			destranca a pthread threadMutex.
		*/
		void unlock();
		
		//! espera por alguma condição de destrancamento
		void waitForUnlockCondition();
		
		//! verifica se a condição de destrancamento foi satisfeita
		/*!
			se estiver esperando, então emite "signal" e 
			libera a pthread de condição threadFlagCVLockUntilSignal
			
		*/
		bool unlockConditionSatisfied();
  };
}

#endif /*THREAD_H_*/
