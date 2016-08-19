#pragma once

StateResult awaitingNameOnBeforeRead(Client *client, ClientState *clientState);
StateResult awaitingNameMainEvent(Client *client, ClientState *state);
StateResult awaitingNameOnAfterRead(Client *client, ClientState *clientState);