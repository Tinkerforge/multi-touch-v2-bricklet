Imports System
Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Multi Touch Bricklet 2.0

    ' Callback subroutine for touch state callback
    Sub TouchStateCB(ByVal sender As BrickletMultiTouchV2, ByVal state As Integer)
        Console.WriteLine("Touch State: " + state.ToString())
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
