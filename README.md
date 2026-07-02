# Seed++

**Seed++** é um sistema automatizado de controle de acesso baseado em RFID, desenvolvido com Arduino para a FnEsc (Física na Escola). O dispositivo utiliza um solenóide acionado por relé para controlar uma fechadura elétrica, oferecendo autenticação segura através de cartões RFID.

O sistema permite o **CRUD de usuários** (Create, Read, Update, Delete), possibilitando registro e remoção individual de cartões ou limpeza total da memória. 

Além de funcional, o projeto serve como **referência de estudo em sistemas embarcados e paradigmas de programação aplicados ao desenvolvimento de hardware**.

## Features

- ✅ Cadastrar novos cartões RFID
- ✅ Remover cartões individualmente
- ✅ Limpar toda a base de cartões
- ✅ Modo administrador e modo leitura
- ✅ Feedback visual
- ✅ Controle de acesso baseado em RFID
- ✅ Armazenamento dinâmico na EEPROM

## Componentes

- Arduino Nano
- Leitor RFID (MFRC522)
- Solenóide com módulo relé
- Módulo regulador de tensão step-down (5V)
- Painel de botões analógicos
- Interruptor ON/OFF com chave de segurança
- Fonte de alimentação 12V

## Arquitetura

O projeto segue paradigmas de **Programação Orientada a Objetos** com separação de responsabilidades:

- `main` - Responsável por orquestrar toda a lógica
- `RFID` - Gerencia leitura de cartões
- `Button` - Interpreta entrada de botões
- `Storage` - Controla armazenamento na EEPROM

## Como Contribuir

O guia para futuros contribuidores está disponível em [CONTRIBUTING.md](CONTRIBUTING.md). Este guia, junto com a documentação técnica, auxilia desenvolvedores que desejam trabalhar na continuidade do projeto.

## Licença

Este projeto está licenciado sob a licença MIT. Para mais detalhes, consulte [LICENSE](LICENSE).
