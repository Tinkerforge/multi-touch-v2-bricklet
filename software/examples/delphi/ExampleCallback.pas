program ExampleCallback;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickletMultiTouchV2;

type
  TExample = class
  private
    ipcon: TIPConnection;
    mt: TBrickletMultiTouchV2;
  public
    procedure TouchStateCB(sender: TBrickletMultiTouchV2; const state: word);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'XYZ'; { Change XYZ to the UID of your Multi Touch Bricklet 2.0 }

var
  e: TExample;

{ Callback procedure for touch state callback }
procedure TExample.TouchStateCB(sender: TBrickletMultiTouchV2; const state: word);
begin
  WriteLn(Format('Touch State: %d', [state]));
end;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  mt := TBrickletMultiTouchV2.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Register touch state callback to procedure TouchStateCB }
  mt.OnTouchState := {$ifdef FPC}@{$endif}TouchStateCB;

  { Set period for touch state callback to 0.01s (10ms) }
  mt.SetTouchStateCallbackConfiguration(10, true);

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
