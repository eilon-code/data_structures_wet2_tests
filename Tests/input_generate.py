import random


class command:
    command_dict = {}

    def __init__(self):
        if not len(command.command_dict):
            command.command_dict[0] = self.fleet
            command.command_dict[1] = self.pirate
            command.command_dict[2] = self.num_ships
            command.command_dict[3] = self.pay
            command.command_dict[4] = self.get_money
            command.command_dict[5] = self.unite
            command.command_dict[6] = self.pirate_argument
            command.command_dict[7] = self.get_rank


    fleet_id_range = 10
    pirate_id_range = 10
    pirate_money_range = 100

    @staticmethod
    def fleet():
        return "add_fleet " + str(random.randint(-2, command.fleet_id_range))

    @staticmethod
    def pirate():
        return (
            "add_pirate "
            + str(random.randint(-2, command.pirate_id_range))
            + " "
            + str(random.randint(-2, command.fleet_id_range))
        )

    @staticmethod
    def num_ships():
        return "num_ships_for_fleet " + str(random.randint(-2, command.fleet_id_range))

    @staticmethod
    def pay():
        return (
            "pay_pirate "
            + str(random.randint(-2, command.pirate_id_range))
            + " "
            + str(random.randint(-2, command.pirate_money_range))
        )

    @staticmethod
    def get_money():
        return "get_pirate_money " + str(random.randint(-2, command.pirate_id_range))
    
    @staticmethod
    def get_rank():
        return "get_pirate_rank " + str(random.randint(-2, command.pirate_id_range))

    @staticmethod
    def unite():
        return (
            "unite_fleets "
            + str(random.randint(-2, command.fleet_id_range))
            + " "
            + str(random.randint(-2, command.fleet_id_range))
        )

    @staticmethod
    def pirate_argument():
        return (
            "pirate_argument "
            + str(random.randint(-2, command.pirate_id_range))
            + " "
            + str(random.randint(-2, command.pirate_id_range))
        )

    @staticmethod
    def generate(add_rank_tests):
        change = 0 if add_rank_tests else 1
        index = random.randint(0, len(command.command_dict)-1-change)
        string = command.command_dict[index]()
        return string

    @staticmethod
    def sizeup_fleet():
        command.fleet_id_range *= 8

    @staticmethod
    def sizeup_pirate():
        command.pirate_id_range *= 8

    @staticmethod
    def sizeup_pirate_money():
        command.pirate_money_range *= 8

    @staticmethod
    def reset():
        command.fleet_id_range = 10
        command.pirate_id_range = 10
        command.pirate_money_range = 100


def generate(length=100, add_rank_tests=True):
    command()
    command.reset()
    string = ""
    for j in range(4):
        for i in range(length // 5):
            string += command.generate(add_rank_tests) + "\n"
        command.sizeup_fleet()
        command.sizeup_pirate()
        command.sizeup_pirate_money()
    return string
