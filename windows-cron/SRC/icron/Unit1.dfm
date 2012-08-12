object ICron: TICron
  OldCreateOrder = False
  DisplayName = 'ICron'
  OnStart = ServiceStart
  Left = 212
  Top = 880
  Height = 200
  Width = 400
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 28
    Top = 24
  end
end
