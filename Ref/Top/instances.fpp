module Ref {

  # ----------------------------------------------------------------------
  # Defaults
  # ----------------------------------------------------------------------

  module Default {
    constant QUEUE_SIZE = 10
    constant STACK_SIZE = 64 * 1024
  }

  # ----------------------------------------------------------------------
  # Active component instances
  # ----------------------------------------------------------------------

  instance blockDrv: Ref.BlockDriver base id 0x0100 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 140

  instance rateGroup1Comp: Svc.ActiveRateGroup base id 0x0200 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 120

  instance rateGroup2Comp: Svc.ActiveRateGroup base id 0x0300 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 119

  instance rateGroup3Comp: Svc.ActiveRateGroup base id 0x0400 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 118

  instance cmdDisp: Svc.CommandDispatcher base id 0x0500 \
    queue size 20 \
    stack size Default.STACK_SIZE \
    priority 101

  instance cmdSeq: Svc.CmdSequencer base id 0x0600 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 100

  instance fileDownlink: Svc.FileDownlink base id 0x0700 \
    queue size 30 \
    stack size Default.STACK_SIZE \
    priority 100

  instance fileManager: Svc.FileManager base id 0x0800 \
    queue size 30 \
    stack size Default.STACK_SIZE \
    priority 100

  instance fileUplink: Svc.FileUplink base id 0x0900 \
    queue size 30 \
    stack size Default.STACK_SIZE \
    priority 100

  instance pingRcvr: Ref.PingReceiver base id 0x0A00 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 100

  instance eventLogger: Svc.ActiveLogger base id 0x0B00 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 98

  # comment in Svc.TlmChan or Svc.TlmPacketizer
  # depending on which form of telemetry downlink
  # you wish to use

  instance tlmSend: Svc.TlmChan base id 0x0C00 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 97

#   instance tlmSend: Svc.TlmPacketizer base id 0x0C00 \
#       queue size Default.QUEUE_SIZE \
#       stack size Default.STACK_SIZE \
#       priority 97

  instance prmDb: Svc.PrmDb base id 0x0D00 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 96

  instance dpCat: Svc.DpCatalog base id 0x0E00 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 96

  instance dpMgr: Svc.DpManager base id 0x0F00 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 96

  instance dpWriter: Svc.DpWriter base id 0x1000 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 96

  # ComQueue has a deeper queue to be resilient to spikes in com throughput
  instance comQueue: Svc.ComQueue base id 0x1100 \
      queue size 50 \
      stack size Default.STACK_SIZE \
      priority 100


  instance typeDemo: Ref.TypeDemo base id 0x1200

  # ----------------------------------------------------------------------
  # Queued component instances
  # ----------------------------------------------------------------------

  instance $health: Svc.Health base id 0x2000 \
    queue size 25

  instance SG1: Ref.SignalGen base id 0x2100 \
    queue size Default.QUEUE_SIZE

  instance SG2: Ref.SignalGen base id 0x2200 \
    queue size Default.QUEUE_SIZE

  instance SG3: Ref.SignalGen base id 0x2300 \
    queue size Default.QUEUE_SIZE

  instance SG4: Ref.SignalGen base id 0x2400 \
    queue size Default.QUEUE_SIZE

  instance SG5: Ref.SignalGen base id 0x2500 \
    queue size Default.QUEUE_SIZE

  instance sendBuffComp: Ref.SendBuff base id 0x2600 \
    queue size Default.QUEUE_SIZE
  


  # ----------------------------------------------------------------------
  # Passive component instances
  # ----------------------------------------------------------------------

  @ Communications driver. May be swapped with other comm drivers like UART
  instance comDriver: Drv.TcpClient base id 0x4000

  instance fatalAdapter: Svc.AssertFatalAdapter base id 0x4100

  instance fatalHandler: Svc.FatalHandler base id 0x4200

  instance commsBufferManager: Svc.BufferManager base id 0x4300

  instance posixTime: Svc.PosixTime base id 0x4400

  instance rateGroupDriverComp: Svc.RateGroupDriver base id 0x4500

  instance recvBuffComp: Ref.RecvBuff base id 0x4600

  instance version: Svc.Version base id 0x4700

  instance textLogger: Svc.PassiveTextLogger base id 0x4800

  instance systemResources: Svc.SystemResources base id 0x4900

  instance dpBufferManager: Svc.BufferManager base id 0x4A00

  instance frameAccumulator: Svc.FrameAccumulator base id 0x4B00

  instance tcDeframer: Svc.CCSDS.TcDeframer base id 0x4C00

  instance spacePacketDeframer: Svc.CCSDS.SpacePacketDeframer base id 0x4D00

  instance tmFramer: Svc.CCSDS.TmFramer base id 0x4E00

  instance spacePacketFramer: Svc.CCSDS.SpacePacketFramer base id 0x4F00

  instance fprimeRouter: Svc.FprimeRouter base id 0x5000

  instance apidManager: Svc.CCSDS.ApidManager base id 0x5100

  instance comStub: Svc.ComStub base id 0x5200

  instance linuxTimer: Svc.LinuxTimer base id 0x5300

}

