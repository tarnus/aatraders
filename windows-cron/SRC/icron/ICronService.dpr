program ICronService;

uses
  SvcMgr,
  Unit1 in 'Unit1.pas' {ICron: TService};

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'ICron';
  Application.CreateForm(TICron, ICron);
  Application.Run;
end.
