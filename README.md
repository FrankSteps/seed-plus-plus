# 🍃 Seed++

**Seed++** é um sistema embarcado de controle de acesso baseado em RFID, desenvolvido com Arduino para o laboratório da **Física na Escola (FnEsc)**. O dispositivo utiliza um solenóide acionado por relé para controlar uma fechadura elétrica, permitindo autenticação segura por meio de cartões RFID.

O sistema foi projetado para gerenciar o acesso ao ambiente de forma automatizada, possibilitando o cadastro, consulta e remoção de cartões autorizados, além da limpeza completa da memória persistente.

Além de sua aplicação prática, o projeto também serve como referência de estudo em **sistemas embarcados**, **arquitetura de software** e **paradigmas de programação aplicados ao desenvolvimento de hardware**.

## Features

- ✅ Cadastro de novos cartões RFID
- ✅ Remoção individual de cartões cadastrados
- ✅ Limpeza completa da base de cartões
- ✅ Modo administrador e modo leitura
- ✅ Feedback visual por LEDs
- ✅ Controle de acesso automatizado
- ✅ Armazenamento persistente em EEPROM

## Hardware

O protótipo utiliza os seguintes componentes:

- Arduino Uno
- Leitor RFID (MFRC522)
- Solenóide com módulo relé
- Módulo regulador de tensão step-down (5V)
- Painel de botões analógicos
- Interruptor ON/OFF com chave de segurança
- LEDs indicadores
- Fonte de alimentação 12V

## Arquitetura de Software

O projeto foi desenvolvido utilizando **Programação Orientada a Objetos (POO)**, com separação clara de responsabilidades entre módulos independentes.

### Módulos principais

- **`main`** — Orquestra a lógica principal do sistema e os modos de operação  
- **`RFID`** — Gerencia a leitura e autenticação dos cartões RFID  
- **`Button`** — Interpreta a entrada dos botões com debounce  
- **`Storage`** — Gerencia o armazenamento persistente na EEPROM  

Essa arquitetura modular facilita manutenção, testes e futuras expansões do sistema.

## Modos de Operação

### Modo Leitura

Modo padrão de operação. O sistema aguarda a aproximação de um cartão RFID e verifica se seu UID está armazenado na EEPROM.

- UID autorizado → acesso liberado  
- UID desconhecido → acesso negado  

### Modo Administrador

Permite gerenciar cartões cadastrados no sistema.

Neste modo é possível:

- Registrar novos cartões
- Remover cartões existentes
- Limpar a base de dados

## Como Contribuir

Contribuições são bem-vindas.

O guia para contribuidores está disponível em `CONTRIBUTING.md`, junto da documentação técnica do projeto, servindo como referência para futuras manutenções e expansões.

## Licença

Este projeto está licenciado sob a licença MIT.

Consulte o arquivo `LICENSE` para mais informações.
