from B_FuncoesFront import *

# Nesta versão, deve ser 1.
QUANTIDADE_DE_JOGADORES = 1

def simular() -> None:
    """
    Descrição:
        Função responsável por executar a tela e puxar toda a aplicação.
    """
    pg.init()

    janela, campo = carregando_visual()

    # Vamos criar nossos objetos e iniciar os trabalhos.
    bola = Bola()
    lista_de_jogadores = []
    for indice_do_jogador in range(
            1,
            QUANTIDADE_DE_JOGADORES + 1
    ):
        lista_de_jogadores.append(
            Jogador(
                indice_do_jogador
            )
        )

    FIM_DE_JOGO = False
    TEMPO_TOTAL = 0
    while not FIM_DE_JOGO:
        for evento in pg.event.get():
            if evento.type == pg.QUIT:
                FIM_DE_JOGO = True

            # Verificação de Teclas Pressionadas
            elif evento.type == pg.KEYDOWN:

                match evento.key:

                    case pg.K_ESCAPE:
                        print(f"\nÚltima posição do mouse registrada: {pg.mouse.get_pos()}")
                        FIM_DE_JOGO = True

                    # Direcionais
                    case pg.K_w:
                        lista_de_jogadores[
                            0
                        ].vel.y += - VEL_DE_IMPULSO_JOGADOR

                    case pg.K_s:
                        lista_de_jogadores[
                            0
                        ].vel.y += VEL_DE_IMPULSO_JOGADOR

                    case pg.K_a:
                        lista_de_jogadores[
                            0
                        ].vel.x += - VEL_DE_IMPULSO_JOGADOR

                    case pg.K_d:
                        lista_de_jogadores[
                            0
                        ].vel.x += VEL_DE_IMPULSO_JOGADOR

                    case pg.K_p:
                        lista_de_jogadores[
                            0
                        ].vel = pg.Vector2(
                            0,
                            0
                        )

                    case _:
                        # Default
                        pass

            # Verificação de Teclas Soltas
            elif evento.type == pg.KEYUP:

                match evento.key:

                    case _:
                        pass

            elif evento.type == pg.MOUSEBUTTONDOWN:
                # 3 É O Esquerdo

                match evento.button:
                    case 3:
                        lista_de_jogadores[
                            0
                        ].segurar_bola(
                            bola
                        )

                    case 1:
                        lista_de_jogadores[
                            0
                        ].iniciar_preparacao_para_chute()

                    case _:
                        pass

            elif evento.type == pg.MOUSEBUTTONUP:
                match evento.button:

                    case 3:
                        lista_de_jogadores[
                            0
                        ].soltar_bola()

                    case 1:
                        lista_de_jogadores[
                            0
                        ].chutar_bola(
                            bola
                        )

                    case _:
                        pass

        # Antes de qualquer coisa

        # Verificações de Gol
        if bola.verificar_se_eh_gol():
            """
            Devíamos ter um goleiro para pegar a bola imediatamente
            e ser capaz de lançá-la à alguem especifico.
            
            Nesta versão, apenas teremos a mensagem de gol e a bola emergirá
            com uma determinada velocidade do meio do gol.
            """

            bola.vel = pg.Vector2(
                0,
                0
            )

            animacao_de_gol(
                janela
            )

            bola.houve_gol()

        # Atualizações na tela
        janela.blit(
            campo,
            (0, 0)
        )

        # Aplicando Física na Bola
        bola.fazer_existir()

        janela.blit(
            bola.imagem,
            bola.POS_IMAGEM
        )

        for jogador in lista_de_jogadores:
            jogador.fazer_existir(
                bola,
                janela
            )

            pg.draw.circle(
                janela,
                jogador.cor,
                jogador.pos,
                TAMANHO_JOGADOR
            )

            janela.blit(
                jogador.texto_do_numero_do_jogador,
                jogador.texto_do_numero_do_jogador.get_rect(
                    center=jogador.pos
                )
            )

            # Dentro de cada jogador, devemos ter um número inerente à ele.

        TEMPO_TOTAL = dispondo_tempo_de_partida(
            TEMPO_TOTAL,
            janela
        )

        dispondo_quantidade_de_gols(
            janela
        )

        pg.time.wait(
            # Milisegundos
            MEDIDOR_DE_FREQUENCIA_DE_FRAMES
        )
        pg.display.flip()
    pg.quit()


if __name__ == '__main__':
    simular()
