#include "raylib.h"
#include "resourceManager.h"

ResourceManager rm = {0};

void loadResources()
{
    rm.menu.normalStartButton = LoadTexture("Assets/Textures/BotaoIniciarNormal.png");
    rm.menu.mouseStartButton = LoadTexture("Assets/Textures/BotaoIniciarMouse.png");
    rm.menu.clickStartButton = LoadTexture("Assets/Textures/BotaoIniciarClicado.png");

    rm.menu.normalLoadButton = LoadTexture("Assets/Textures/BotaoCarregarNormal.png");
    rm.menu.mouseLoadButton = LoadTexture("Assets/Textures/BotaoCarregarMouse.png");
    rm.menu.clickLoadButton = LoadTexture("Assets/Textures/BotaoCarregarClicado.png");

    rm.menu.Save1LoadButton = LoadTexture("Assets/Textures/BotaoSave1.png");
    rm.menu.Save2LoadButton = LoadTexture("Assets/Textures/BotaoSave2.png");
    rm.menu.Save3LoadButton = LoadTexture("Assets/Textures/BotaoSave3.png");
    rm.menu.BackMenuButton = LoadTexture("Assets/Textures/BotaoVoltarMenu.png");

    rm.menu.normalHelpButton = LoadTexture("Assets/Textures/BotaoAjudaNormal.png");
    rm.menu.mouseHelpButton = LoadTexture("Assets/Textures/BotaoAjudaMouse.png");
    rm.menu.clickHelpButton = LoadTexture("Assets/Textures/BotaoAjudaClick.png");

    rm.menu.normalCloseButton = LoadTexture("Assets/Textures/BotaoFecharNormal.png");
    rm.menu.mouseCloseButton = LoadTexture("Assets/Textures/BotaoFecharMouse.png");
    rm.menu.clickCloseButton = LoadTexture("Assets/Textures/BotaoFecharClick.png");


    rm.menu.bigNormalStartButton = LoadTexture("Assets/Textures/BotaoIniciarNormalGrande.png");
    rm.menu.bigMouseStartButton = LoadTexture("Assets/Textures/BotaoIniciarMouseGrande.png");

    rm.menu.bigNormalLoadButton = LoadTexture("Assets/Textures/BotaoCarregarNormalGrande.png");
    rm.menu.bigMouseLoadButton = LoadTexture("Assets/Textures/BotaoCarregarMouseGrande.png");

    rm.menu.bigSave1LoadButton = LoadTexture("Assets/Textures/BotaoSave1Grande.png");
    rm.menu.bigSave2LoadButton = LoadTexture("Assets/Textures/BotaoSave2Grande.png");
    rm.menu.bigSave3LoadButton = LoadTexture("Assets/Textures/BotaoSave3Grande.png");
    rm.menu.bigBackMenuButton = LoadTexture("Assets/Textures/BotaoVoltarMenuGrande.png");

    rm.menu.bigNormalHelpButton = LoadTexture("Assets/Textures/BotaoAjudaNormalGrande.png");
    rm.menu.bigMouseHelpButton = LoadTexture("Assets/Textures/BotaoAjudaMouseGrande.png");

    rm.menu.bigNormalCloseButton = LoadTexture("Assets/Textures/BotaoFecharNormalGrande.png");
    rm.menu.bigMouseCloseButton = LoadTexture("Assets/Textures/BotaoFecharMouseGrande.png");


    rm.pause.normalReturnButton = LoadTexture("Assets/Textures/BotaoRetomarNormal.png");
    rm.pause.mouseReturnButton = LoadTexture("Assets/Textures/BotaoRetomarMouse.png");

    rm.pause.normalSaveButton = LoadTexture("Assets/Textures/BotaoSalvarNormal.png");
    rm.pause.mouseSaveButton = LoadTexture("Assets/Textures/BotaoSalvarMouse.png");

    rm.pause.normalLeaveButton = LoadTexture("Assets/Textures/BotaoSairNormal.png");
    rm.pause.mouseLeaveButton = LoadTexture("Assets/Textures/BotaoSairMouse.png");

    rm.pause.FullscreenButton = LoadTexture("Assets/Textures/BotaoAumentarTela.png");

    rm.pause.normalReturnButtonG = LoadTexture("Assets/Textures/BotaoRetomarNormalGrande.png");
    rm.pause.mouseReturnButtonG = LoadTexture("Assets/Textures/BotaoRetomarMouseGrande.png");

    rm.pause.normalSaveButtonG = LoadTexture("Assets/Textures/BotaoSalvarNormalGrande.png");
    rm.pause.mouseSaveButtonG = LoadTexture("Assets/Textures/BotaoSalvarMouseGrande.png");

    rm.pause.normalLeaveButtonG = LoadTexture("Assets/Textures/BotaoSairNormalGrande.png");
    rm.pause.mouseLeaveButtonG = LoadTexture("Assets/Textures/BotaoSairMouseGrande.png");

    rm.pause.MinimizeButton = LoadTexture("Assets/Textures/BotaoMinimizarTela.png");



    rm.gl.bench = LoadTexture("Assets/Textures/Banch.png");
    rm.gl.grass = LoadTexture("Assets/Textures/grassBlock.png");
    rm.gl.store = LoadTexture("Assets/Textures/store.png");
    rm.gl.storeWall = LoadTexture ("Assets/Textures/FundoLoja.png");
    rm.gl.storeBlock = LoadTexture ("Assets/Textures/BlocoLoja.png");
    rm.gl.SpriteComputer = LoadTexture ("Assets/Textures/Computador.png");




    rm.gw.defaultTile = LoadTexture("Assets/Textures/DefaultTile.png");

    rm.gw.horizontalPowerA = LoadTexture("Assets/Textures/HorizontalPowerA.png");
    rm.gw.horizontalPowerB = LoadTexture("Assets/Textures/HorizontalPowerB.png");

    rm.gw.ticketRU= LoadTexture("Assets/Textures/TicketRU.png");

    rm.gw.glitch1 = LoadTexture("Assets/Textures/glitchA.png");
    rm.gw.glitch2 = LoadTexture("Assets/Textures/glitchB.png");
    rm.gw.skullBug[0] = LoadTexture ("Assets/Textures/skullBug1.png");
    rm.gw.skullBug[1] = LoadTexture ("Assets/Textures/skullBug2.png");
    rm.gw.sleepingBoss = LoadTexture("Assets/Textures/sleepingBoss.png");
    rm.gw.bossActive = LoadTexture("Assets/Textures/bossActive.png");

    rm.gw.portal = LoadTexture("Assets/Textures/portal.png");



    rm.player.sevenHearts = LoadTexture("Assets/Textures/7corações.png");
    rm.player.sixHearts = LoadTexture("Assets/Textures/6corações.png");
    rm.player.fiveHearts = LoadTexture("Assets/Textures/5corações.png");
    rm.player.fourHearts = LoadTexture("Assets/Textures/4corações.png");
    rm.player.treeHearts = LoadTexture("Assets/Textures/3corações.png");
    rm.player.twoHearts = LoadTexture("Assets/Textures/2corações.png");
    rm.player.oneHearts = LoadTexture("Assets/Textures/1corações.png");

    rm.player.hit7Heart = LoadTexture("Assets/Textures/hit7heart.png");
    rm.player.hit6Heart = LoadTexture("Assets/Textures/hit6heart.png");
    rm.player.hit5Heart = LoadTexture("Assets/Textures/hit5heart.png");
    rm.player.hit4Heart = LoadTexture("Assets/Textures/hit4heart.png");
    rm.player.hit3Heart = LoadTexture("Assets/Textures/hit3heart.png");
    rm.player.hit2Heart = LoadTexture("Assets/Textures/hit2heart.png");

    rm.player.sevenHeartsG = LoadTexture("Assets/Textures/7coraçõesG.png");
    rm.player.sixHeartsG = LoadTexture("Assets/Textures/6coraçõesG.png");
    rm.player.fiveHeartsG = LoadTexture("Assets/Textures/5coraçõesG.png");
    rm.player.fourHeartsG = LoadTexture("Assets/Textures/4coraçõesG.png");
    rm.player.treeHeartsG = LoadTexture("Assets/Textures/3coraçõesG.png");
    rm.player.twoHeartsG = LoadTexture("Assets/Textures/2coraçõesG.png");
    rm.player.oneHeartsG = LoadTexture("Assets/Textures/1coraçõesG.png");

    rm.player.hit7HeartG = LoadTexture("Assets/Textures/hit7heartG.png");
    rm.player.hit6HeartG = LoadTexture("Assets/Textures/hit6heartG.png");
    rm.player.hit5HeartG = LoadTexture("Assets/Textures/hit5heartG.png");
    rm.player.hit4HeartG = LoadTexture("Assets/Textures/hit4heartG.png");
    rm.player.hit3HeartG = LoadTexture("Assets/Textures/hit3heartG.png");
    rm.player.hit2HeartG = LoadTexture("Assets/Textures/hit2heartG.png");

    rm.player.zeroAura = LoadTexture("Assets/Textures/0aura.png");
    rm.player.oneAura = LoadTexture("Assets/Textures/1aura.png");
    rm.player.twoAura = LoadTexture("Assets/Textures/2aura.png");
    rm.player.treeAura = LoadTexture("Assets/Textures/3aura.png");
    rm.player.fourAura = LoadTexture("Assets/Textures/4aura.png");
    rm.player.fiveAura = LoadTexture("Assets/Textures/5aura.png");
    rm.player.sixAura = LoadTexture("Assets/Textures/6aura.png");
    rm.player.sevenAura = LoadTexture("Assets/Textures/7aura.png");
    rm.player.eightAura = LoadTexture("Assets/Textures/8aura.png");
    rm.player.nineAura = LoadTexture("Assets/Textures/9aura.png");
    rm.player.tenAura = LoadTexture("Assets/Textures/10aura.png");
    rm.player.elevenAura = LoadTexture("Assets/Textures/11aura.png");
    rm.player.twelveAura = LoadTexture("Assets/Textures/12aura.png");


    rm.player.zeroAuraG = LoadTexture("Assets/Textures/0auraGrande.png");
    rm.player.oneAuraG = LoadTexture("Assets/Textures/1auraGrande.png");
    rm.player.twoAuraG = LoadTexture("Assets/Textures/2auraGrande.png");
    rm.player.treeAuraG = LoadTexture("Assets/Textures/3auraGrande.png");
    rm.player.fourAuraG = LoadTexture("Assets/Textures/4auraGrande.png");
    rm.player.fiveAuraG = LoadTexture("Assets/Textures/5auraGrande.png");
    rm.player.sixAuraG = LoadTexture("Assets/Textures/6auraGrande.png");
    rm.player.sevenAuraG = LoadTexture("Assets/Textures/7auraGrande.png");
    rm.player.eightAuraG = LoadTexture("Assets/Textures/8auraGrande.png");
    rm.player.nineAuraG = LoadTexture("Assets/Textures/9auraGrande.png");
    rm.player.tenAuraG = LoadTexture("Assets/Textures/10auraGrande.png");
    rm.player.elevenAuraG = LoadTexture("Assets/Textures/11auraGrande.png");
    rm.player.twelveAuraG = LoadTexture("Assets/Textures/12auraGrande.png");

    rm.player.auraLeek = LoadTexture("Assets/Textures/auraLeek.png");
    rm.player.auraLeekG = LoadTexture("Assets/Textures/auraLeekG.png");

    rm.player.ticketsRU1 = LoadTexture("Assets/Textures/ticketRU1.png");
    rm.player.ticketsRU2 = LoadTexture("Assets/Textures/ticketRU2.png");
    rm.player.ticketsRU1G = LoadTexture("Assets/Textures/ticketRU1G.png");
    rm.player.ticketsRU2G = LoadTexture("Assets/Textures/ticketRU2G.png");

    rm.player.restingPlayer[0] = LoadTexture("Assets/Textures/restingPlayer.png");
    rm.player.restingPlayer[1] = LoadTexture("Assets/Textures/restingPlayer2.png");
    rm.player.normalPlayer = LoadTexture("Assets/Textures/normalPlayer.png");
    rm.player.playerRunning[0] = LoadTexture("Assets/Textures/playerRunning.png");
    rm.player.playerRunning[1] = LoadTexture("Assets/Textures/playerRunning2.png");
    rm.player.playerJumping[0] = LoadTexture("Assets/Textures/playerJumping.png");
    rm.player.playerJumping[1] = LoadTexture("Assets/Textures/playerJumping2.png");
    rm.player.playerFalling[0] = LoadTexture("Assets/Textures/playerFalling.png");
    rm.player.playerFalling[1] = LoadTexture("Assets/Textures/playerFalling2.png");
    rm.player.playerDash = LoadTexture("Assets/Textures/playerDash.png");
    rm.player.playerDoubleJump = LoadTexture("Assets/Textures/playerDoubleJump.png");
    rm.player.playerChiclete = LoadTexture("Assets/Textures/playerChiclete.png");
    rm.player.playerAttack = LoadTexture("Assets/Textures/playerAttacks.png");
    rm.player.playerAttackUp = LoadTexture("Assets/Textures/playerAttackUp.png");
    rm.player.playerJumpAttackUp = LoadTexture("Assets/Textures/playerJumpAttackUp.png");
    rm.player.playerAttackDown = LoadTexture("Assets/Textures/playerAttackDown.png");
    rm.player.playerHealing = LoadTexture("Assets/Textures/playerHealing.png");

    rm.player.swordAttack = LoadTexture("Assets/Textures/swordAttack.png");


    rm.charm.gamerHeart = LoadTexture("Assets/Textures/gamerHeart.png");
    rm.charm.programmerHands = LoadTexture("Assets/Textures/programmerHands.png");
    rm.charm.goldTickets = LoadTexture("Assets/Textures/goldTickets.png");
    rm.charm.debugSword = LoadTexture("Assets/Textures/debugSword.png");
    rm.charm.plusEgo = LoadTexture("Assets/Textures/plusEgo.png");




    rm.defaultMusic = LoadMusicStream("assets/sounds/Crossroads.mp3");
    rm.bossMusic = LoadMusicStream("assets/sounds/Decisive Battle.mp3");


}

void unloadResouces()
{
    UnloadTexture(rm.menu.normalStartButton);
    UnloadTexture(rm.menu.mouseStartButton);
    UnloadTexture(rm.menu.clickStartButton );

    UnloadTexture(rm.menu.normalLoadButton);
    UnloadTexture(rm.menu.mouseLoadButton);
    UnloadTexture(rm.menu.clickLoadButton);

    UnloadTexture(rm.menu.Save1LoadButton);
    UnloadTexture(rm.menu.Save2LoadButton);
    UnloadTexture(rm.menu.Save3LoadButton);
    UnloadTexture(rm.menu.BackMenuButton);

    UnloadTexture(rm.menu.normalHelpButton);
    UnloadTexture(rm.menu.mouseHelpButton);
    UnloadTexture(rm.menu.clickHelpButton);

    UnloadTexture(rm.menu.normalCloseButton);
    UnloadTexture(rm.menu.mouseCloseButton);
    UnloadTexture(rm.menu.clickCloseButton);


    UnloadTexture(rm.menu.bigNormalStartButton);
    UnloadTexture(rm.menu.bigMouseStartButton );

    UnloadTexture(rm.menu.bigNormalLoadButton);
    UnloadTexture(rm.menu.bigMouseLoadButton);

    UnloadTexture(rm.menu.bigSave1LoadButton);
    UnloadTexture(rm.menu.bigSave2LoadButton);
    UnloadTexture(rm.menu.bigSave3LoadButton);
    UnloadTexture(rm.menu.bigBackMenuButton);

    UnloadTexture(rm.menu.bigNormalHelpButton);
    UnloadTexture(rm.menu.bigMouseHelpButton);

    UnloadTexture(rm.menu.bigNormalCloseButton);
    UnloadTexture(rm.menu.bigMouseCloseButton);

    UnloadTexture(rm.pause.normalReturnButton);
    UnloadTexture(rm.pause.mouseReturnButton);

    UnloadTexture(rm.pause.normalSaveButton);
    UnloadTexture(rm.pause.mouseSaveButton);

    UnloadTexture(rm.pause.normalLeaveButton);
    UnloadTexture(rm.pause.mouseLeaveButton);

    UnloadTexture(rm.pause.FullscreenButton);

    UnloadTexture(rm.pause.normalReturnButtonG);
    UnloadTexture(rm.pause.mouseReturnButtonG);

    UnloadTexture(rm.pause.normalSaveButtonG);
    UnloadTexture(rm.pause.mouseSaveButtonG);

    UnloadTexture(rm.pause.normalLeaveButtonG);
    UnloadTexture(rm.pause.mouseLeaveButtonG);

    UnloadTexture(rm.pause.MinimizeButton);



    UnloadTexture(rm.gl.bench);
    UnloadTexture(rm.gl.store);
    UnloadTexture(rm.gl.grass);
    UnloadTexture(rm.gl.storeWall);
    UnloadTexture(rm.gl.storeBlock);
    UnloadTexture(rm.gl.SpriteComputer);


    UnloadTexture(rm.gw.defaultTile);

    UnloadTexture(rm.gw.horizontalPowerA);
    UnloadTexture(rm.gw.horizontalPowerB);

    UnloadTexture(rm.gw.ticketRU);

    UnloadTexture(rm.gw.glitch1);
    UnloadTexture(rm.gw.glitch2);
    UnloadTexture(rm.gw.skullBug[0]);
    UnloadTexture(rm.gw.skullBug[1]);
    UnloadTexture(rm.gw.bossActive);
    UnloadTexture(rm.gw.sleepingBoss);
    UnloadTexture(rm.gw.portal);



    UnloadTexture(rm.player.sevenHearts);
    UnloadTexture(rm.player.sixHearts);
    UnloadTexture(rm.player.fiveHearts );
    UnloadTexture(rm.player.fourHearts );
    UnloadTexture(rm.player.treeHearts );
    UnloadTexture(rm.player.twoHearts );
    UnloadTexture(rm.player.oneHearts );

    UnloadTexture(rm.player.hit7Heart);
    UnloadTexture(rm.player.hit6Heart);
    UnloadTexture(rm.player.hit5Heart);
    UnloadTexture(rm.player.hit4Heart);
    UnloadTexture(rm.player.hit3Heart);
    UnloadTexture(rm.player.hit2Heart);

    UnloadTexture(rm.player.hit7HeartG);
    UnloadTexture(rm.player.hit6HeartG);
    UnloadTexture(rm.player.hit5HeartG);
    UnloadTexture(rm.player.hit4HeartG);
    UnloadTexture(rm.player.hit3HeartG);
    UnloadTexture(rm.player.hit2HeartG);

    UnloadTexture(rm.player.sevenHeartsG);
    UnloadTexture(rm.player.sixHeartsG);
    UnloadTexture(rm.player.fiveHeartsG );
    UnloadTexture(rm.player.fourHeartsG );
    UnloadTexture(rm.player.treeHeartsG );
    UnloadTexture(rm.player.twoHeartsG );
    UnloadTexture(rm.player.oneHeartsG );

    UnloadTexture(rm.player.zeroAura);
    UnloadTexture(rm.player.oneAura);
    UnloadTexture(rm.player.twoAura);
    UnloadTexture(rm.player.treeAura);
    UnloadTexture(rm.player.fourAura);
    UnloadTexture(rm.player.fiveAura);
    UnloadTexture(rm.player.sixAura);
    UnloadTexture(rm.player.sevenAura);
    UnloadTexture(rm.player.eightAura);
    UnloadTexture(rm.player.nineAura);
    UnloadTexture(rm.player.tenAura);
    UnloadTexture(rm.player.elevenAura);
    UnloadTexture(rm.player.twelveAura);

    UnloadTexture(rm.player.zeroAuraG);
    UnloadTexture(rm.player.oneAuraG);
    UnloadTexture(rm.player.twoAuraG);
    UnloadTexture(rm.player.treeAuraG);
    UnloadTexture(rm.player.fourAuraG);
    UnloadTexture(rm.player.fiveAuraG);
    UnloadTexture(rm.player.sixAuraG);
    UnloadTexture(rm.player.sevenAuraG);
    UnloadTexture(rm.player.eightAuraG);
    UnloadTexture(rm.player.nineAuraG);
    UnloadTexture(rm.player.tenAuraG);
    UnloadTexture(rm.player.elevenAuraG);
    UnloadTexture(rm.player.twelveAuraG);

    UnloadTexture(rm.player.auraLeek);
    UnloadTexture(rm.player.auraLeekG);

    UnloadTexture(rm.player.ticketsRU1);
    UnloadTexture(rm.player.ticketsRU2);

    UnloadTexture(rm.player.ticketsRU1G);
    UnloadTexture(rm.player.ticketsRU2G);

    UnloadTexture(rm.player.restingPlayer[0]);
    UnloadTexture(rm.player.restingPlayer[1]);
    UnloadTexture(rm.player.normalPlayer);
    UnloadTexture(rm.player.playerRunning[0]);
    UnloadTexture(rm.player.playerRunning[1]);
    UnloadTexture(rm.player.playerJumping[0]);
    UnloadTexture(rm.player.playerJumping[1]);
    UnloadTexture(rm.player.playerFalling[0]);
    UnloadTexture(rm.player.playerFalling[1]);
    UnloadTexture(rm.player.playerDash);
    UnloadTexture(rm.player.playerDoubleJump );
    UnloadTexture(rm.player.playerChiclete);
    UnloadTexture(rm.player.playerAttack);
    UnloadTexture(rm.player.playerAttackUp);
    UnloadTexture(rm.player.playerJumpAttackUp);
    UnloadTexture(rm.player.playerAttackDown);
    UnloadTexture(rm.player.playerHealing);

    UnloadTexture(rm.player.swordAttack);


    UnloadTexture(rm.charm.gamerHeart);
    UnloadTexture(rm.charm.programmerHands);
    UnloadTexture(rm.charm.goldTickets);
    UnloadTexture(rm.charm.plusEgo);
    UnloadTexture(rm.charm.debugSword);

    UnloadMusicStream(rm.defaultMusic);
    UnloadMusicStream(rm.bossMusic);
}
