import serial

port = 'COM4'
BAUDRATE = 9600

ard = serial.Serial(port, BAUDRATE)

def Decode(A) :
    A = A.decode()
    A = str(A)
    if A[0] == '6' : # and A[-1] == 'T' :
        #if (len(A)==14) :
        Ard1 = str(A[3:-2])
        #Ard2 = str(A[7:])
        result = [Ard1]
        return result
        
    '''    
    else :
        print("Error_lack of number _ %d" %len(A))
        return False

    else :
        print("Error_Wrong Signal1")
        return False
    '''

def make_file() :
    s1 = 'Light'
    s2 = 'Current_PPFD'
    s3 = 'Humidity'
    s4 = 'Temperature'
    s5 = 'Soil_Moisture'

    if ard.readable() :
        line = ard.readline()
        code = Decode(line)

        if s1 and s2 and s3 and s4 and s5 in str(code) :
            with open( "sensor_value.txt", mode = "w") as file :
                file.write(str(code[0]))
                
                print('code: ',)
                
        else :
            pass
        
    else :
        print("Fail Form ArdRead")


    





            
