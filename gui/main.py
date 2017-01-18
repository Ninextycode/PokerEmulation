from tkinter import  *


class PlayerLabel(Frame):
    def __init__(self, parent, name):
        Frame.__init__(self, parent)
        self.grid()
        self.name = Label(self, text=name)
        self.name.grid(row=0, column=0)

        self.cards = Label(self)
        self.cards.grid(row=1, column=0)

        self.chips = Label(self)
        self.chips.grid(row=2, column=0)

        self.this_bet = Label(self)
        self.this_bet.grid(row=1, column=1)

    def deal_cards(self, cards):
        self.cards["text"] = str(cards)

    def give_chips(self, chips):
        self.chips["text"] = str(chips)

    def make_bet(self, bet):
        self.this_bet["text"] = str(int("0"+self.this_bet["text"]) + int(bet))
        self.chips["text"] = str(int(self.chips["text"]) - int(bet))

    def collect_bet(self):
        self.this_bet["text"] = ""

    def put_button(self):
        self.name["text"] += " *"

    def remore_button(self):
        self.name["text"] = self.name["text"][:-2]


class Window(Frame):
    def __init__(self, parent, number_of_players):
        Frame.__init__(self, parent)
        self.master.title = "Poker"
        self.players = []

    def change_player_state(self, player_index, content):
        pass;

root = Tk()
mf = PlayerLabel(root, "Maxim")
mf.give_chips(10)
mf.deal_cards("AsAd")
mf.make_bet(1)

mf.mainloop()