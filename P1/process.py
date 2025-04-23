class Process():
    def __init__(self, parent_num : int, index : int):
        self.parent = parent_num
        self.index = index
        self.state = 1 # 1 indicates it is in the Ready state, whereas 0 indiicates it is blocked
        pass

    def create():
        """
        TODO: 
        1. Allocate new PCB (create module with PCB Class)
        2. set its state to ready.
        3. insert it into its parent's children list
        4. set its parent
        5. intitialize its children list
        6. initialize its resources list
        7. Insert into ready list
        8. display "Process j Created"
        """