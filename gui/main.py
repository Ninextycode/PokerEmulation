from tkinter import *
import math


class PlayerLabel(Frame):
    def __init__(self, parent, name):
        super().__init__(parent, width=100, height=100)
        self.grid()
        self.name = Label(self, text=name)
        self.name.grid(row=0)

        self.cards = Label(self)
        self.cards.grid(row=1)

        self.money = Label(self)
        self.money.grid(row=2)

        self.this_bet = Label(self)
        self.this_bet.grid(row=3)

        self.config(highlightbackground="black", highlightthickness=1)

        self.columnconfigure(0, minsize=80)  # needed to center the content

    def deal_cards(self, cards):
        self.cards["text"] = str(cards)

    def give_money(self, money):
        self.money["text"] = str(money)

    def make_bet(self, bet):
        self.this_bet["text"] = str(int("0"+self.this_bet["text"]) + int(bet))
        self.money["text"] = str(int(self.money["text"]) - int(bet))

    def collect_bet(self):
        bet = int("0" + self.this_bet["text"])
        self.this_bet["text"] = ""
        return bet

    def put_button(self):
        self.name["text"] += " *"

    def remore_button(self):
        self.name["text"] = self.name["text"][:-2]


class Center(Frame):
    def __init__(self, parent):
        super().__init__(parent)
        self.grid()

        self.cards = Label(self)
        self.cards.grid(row=0, column=0)

        self.money = Label(self)
        self.money.grid(row=1, column=0)

    def add_card(self, card):
        self.cards["text"] += str(card)

    def add_money(self, money):
        self.money["text"] = str(int("0"+ self.cards["money"]) + money)

    def collect_money(self):
        self.money["text"] = ""


class ControlPaner(Frame):
    def __init__(self, parent, player):
        super().__init__(parent)
        self.player = player
        self.grid()
        self.betButton = Button(self, text="Bet", command=self.bet)
        self.betButton.grid(row=0, column=0)

        self.bet_amount = IntVar()
        self.slider = Scale(self, resolution=1, variable=self.bet_amount, orient=HORIZONTAL, from_=0, to=player["money"])
        self.slider.grid(row=0, column=1)

        self.columnconfigure(0, weight=1)
        self.columnconfigure(1, weight=3)
        self.columnconfigure(2, weight=1)

        self.bet_amount_entry = Entry(self, bg="#ffffff", width=6, textvariable=self.bet_amount)
        self.bet_amount_entry.grid(row=0, column=2)

    def bet(self):
        # here player does action
        pass

    def set_player(self):
        # here we can change controlled player
        pass


class Table(Frame):
    def __init__(self, parent, players):
        super().__init__(parent)
        self.pack_propagate(False)
        self.grid()
        self.master.title = "Poker"
        self.players = {}

        n = math.ceil(len(players)/4) + 2

        row = 0
        column = 1
        state = 0
        for player in players:
            playerL = PlayerLabel(self, player["name"])
            self.players[player["name"]] = playerL
            playerL.give_money(player["money"])
            playerL.grid(row=row, column=column, pady=5, padx=5,  sticky=NSEW)
            if state == 0:
                column += 1
                if column == n-1:
                    state = 1
                    row = 1
                    column = n -1
            elif state == 1:
                row += 1
                if row == n - 1:
                    state = 2
                    row = n -1
                    column = n - 2
            elif state == 2:
                column -= 1
                if column == 0:
                    state = 3
                    column = 0
                    row = n - 2
            elif state == 3:
                row -= 1

        for i in range(n):
            self.rowconfigure(i, minsize=80)
            self.columnconfigure(i, minsize=80)

        self.table = Center(self)
        self.table.grid(row=1, column=1, columnspan=n-2, rowspan=n-2)

        self.controls = ControlPaner(self, players[0])
        self.controls.grid(row=n+1, column=0, columnspan=n, sticky=NSEW)

    def player_bet(self, player_name, bet):
        self.players[player_name].make_bet(bet)

    def player_deal_cards(self, player_name, bet):
        self.players[player_name].deal_cards(bet)

    def deal_community_cards(self, cards):
        for card in cards:
            self.table.add_card(card)

    def end_street(self, player_name, bet):
        collected = 0
        for _, player in self.players.items():
            collected += player.collect_bet()
        self.table.add_money(collected)

    def add_card(self, card):
        self.table.add_card(card)

root = Tk()


win = Table(root, [
    {"name": "Maxim", "money": 10},
    {"name": "Sec", "money": 10},
])

win.player_deal_cards("Maxim", "AsAc")
win.player_bet("Maxim", 10)
win.deal_community_cards(["2s", "7c", "Ah"])
win.mainloop()