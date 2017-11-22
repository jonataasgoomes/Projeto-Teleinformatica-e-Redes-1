#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("FirstScriptExample");


int main(int argc, char const *argv[])
{
    LogComponentEnable("UdpEchoClientApplication",LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication",LOG_LEVEL_INFO);

    NodeContainer nodes;
    nodes.Create(2);
    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate",StrinValue("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay"),StringValue("2ms");

    NetDeviceContainer devices;
    devices = pointToPoint.Install(nodes);

    internetStackHelper stack;
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0","255.255.255.0");

    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    UdpEchoServerHelper echoServer(9);

    ApplicationContainer serverApps = echoServer.Install(nodesget(1));
    serverApps.Start(Seconds(0.0));
    serverApps.Stop(Seconds(10.0));

    UdpEchoClientHelper echoClient(interfaces.GetAddress(1),9);
    echoClient.SetAttribute("MaxPackets",UintegerValue(10));
    echoClient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
    echoClient.SetAttribute("PacketSize",UintegerValue(1024));

    ApplicationContainer clientApps = echoClient.Install(nodesGet(0));
    clientApps.Start(Seconds(0.0));
    clientApps.Stop(Seconds(10.0));

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
