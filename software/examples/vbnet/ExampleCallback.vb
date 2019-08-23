Imports System
Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Multi Touch Bricklet 2.0

    ' Callback subroutine for touch state callback
    Sub TouchStateCB(ByVal sender As BrickletMultiTouchV2, ByVal state As Boolean())
        Console.WriteLine("Electrode 0: " + state(0).ToString())
        Console.WriteLine("Electrode 1: " + state(1).ToString())
        Console.WriteLine("Electrode 2: " + state(2).ToString())
        Console.WriteLine("Electrode 3: " + state(3).ToString())
        Console.WriteLine("Electrode 4: " + state(4).ToString())
        Console.WriteLine("Electrode 5: " + state(5).ToString())
        Console.WriteLine("Electrode 6: " + state(6).ToString())
        Console.WriteLine("Electrode 7: " + state(7).ToString())
        Console.WriteLine("Electrode 8: " + state(8).ToString())
        Console.WriteLine("Electrode 9: " + state(9).ToString())
        Console.WriteLine("Electrode 10: " + state(10).ToString())
        Console.WriteLine("Electrode 11: " + state(11).ToString())
        Console.WriteLine("Proximity: " + state(12).ToString())
        Console.WriteLine("")
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim mt As New BrickletMultiTouchV2(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register touch state callback to subroutine TouchStateCB
        AddHandler mt.TouchStateCallback, AddressOf TouchStateCB

        ' Set period for touch state callback to 0.01s (10ms)
        mt.SetTouchStateCallbackConfiguration(10, True)

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
