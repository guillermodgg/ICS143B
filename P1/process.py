class Process():
    def __init__(self, parent_num : int):
        self.parent = parent_num
        self.state = 1 # 1 indicates it is in the Ready state, whereas 0 indiicates it is blocked
        pass