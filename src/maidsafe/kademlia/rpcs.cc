/* Copyright (c) 2009 maidsafe.net limited
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
    * Neither the name of the maidsafe.net limited nor the names of its
    contributors may be used to endorse or promote products derived from this
    software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "maidsafe/kademlia/kadrpc.h"
#include "maidsafe/kademlia/kadid.h"
#include "maidsafe/transport/transport.h"
#include "maidsafe/transport/udttransport.h"

namespace kademlia {
// TODO(dirvine) Dec 12 2010 - template this to take mutiple
// transports to support tcp as well as reliable udp

template <class T>
KadRpcs::KadRpcs(T) {
      // Create a transport object for each RPC
      boost::shared_ptr<transport::Transport>
                        transport_(new T);
//       transport_->signals()->ConnectOnMessageReceived();
}

void KadRpcs::FindNode(const KadId &key, const Endpoint &ep,
                       FindResponse *resp) {
  FindRequest args;
  args.set_key(key.String());
  ContactInfo *sender_info = args.mutable_sender_info();
  *sender_info = info_;
// XXXXXX
// connect to a receive slot
  KademliaService::Stub service(channel);
  service.FindNode(ctler, &args, resp, callback);
  delete channel;
}

void KadRpcs::FindValue(const KadId &key, const IP &ip, const Port &port,
                        const IP &rendezvous_ip, const Port &rendezvous_port,
                        FindResponse *resp, rpcprotocol::Controller *ctler,
                        google::protobuf::Closure *callback) {
  FindRequest args;
  args.set_key(key.String());
  ContactInfo *sender_info = args.mutable_sender_info();
  *sender_info = info_;
  rpcprotocol::Channel *channel;
//   if (has_transport_)
//     channel = new rpcprotocol::Channel(channel_manager_, ip,
//                                        port, "", 0, rendezvous_ip,
//                                        rendezvous_port);
//   else
    channel = new rpcprotocol::Channel(channel_manager_, ip, port,
                                       rendezvous_ip, rendezvous_port);
  KademliaService::Stub service(channel);
  service.FindValue(ctler, &args, resp, callback);
  delete channel;
}

void KadRpcs::Ping(const IP &ip, const Port &port, const IP &rendezvous_ip,
                   const Port &rendezvous_port, PingResponse *resp,
                   rpcprotocol::Controller *ctler,
                   google::protobuf::Closure *callback) {
  PingRequest args;
  args.set_ping("ping");
  ContactInfo *sender_info = args.mutable_sender_info();
  *sender_info = info_;
  rpcprotocol::Channel *channel;
//   if (has_transport_)
//     channel = new rpcprotocol::Channel(channel_manager_, transport_, ip,
//                                        port, "", 0, rendezvous_ip,
//                                        rendezvous_port);
//   else
    channel = new rpcprotocol::Channel(channel_manager_, ip, port,
                                       rendezvous_ip, rendezvous_port);
  KademliaService::Stub service(channel);
  service.Ping(ctler, &args, resp, callback);
  delete channel;
}

void KadRpcs::Store(const KadId &key, const SignedValue &value,
                    const SignedRequest &sig_req, const IP &ip,
                    const Port &port, const IP &rendezvous_ip,
                    const Port &rendezvous_port, StoreResponse *resp,
                    rpcprotocol::Controller *ctler,
                    google::protobuf::Closure *callback,
                    const boost::int32_t &ttl, const bool &publish) {
  StoreRequest args;
  args.set_key(key.String());
  SignedValue *svalue = args.mutable_sig_value();
  *svalue = value;
  args.set_ttl(ttl);
  args.set_publish(publish);
  SignedRequest *sreq = args.mutable_signed_request();
  *sreq = sig_req;
  ContactInfo *sender_info = args.mutable_sender_info();
  *sender_info = info_;
  rpcprotocol::Channel *channel;
//   if (has_transport_)
//     channel = new rpcprotocol::Channel(channel_manager_, transport_, ip,
//                                        port, "", 0, rendezvous_ip,
//                                        rendezvous_port);
//   else
    channel = new rpcprotocol::Channel(channel_manager_, ip, port,
                                       rendezvous_ip, rendezvous_port);
  KademliaService::Stub service(channel);
  service.Store(ctler, &args, resp, callback);
  delete channel;
}

void KadRpcs::Store(const KadId &key, const std::string &value,
                    const IP &ip, const Port &port, const IP &rendezvous_ip,
                    const Port &rendezvous_port, StoreResponse *resp,
                    rpcprotocol::Controller *ctler,
                    google::protobuf::Closure *callback,
                    const boost::int32_t &ttl, const bool &publish) {
  StoreRequest args;
  args.set_key(key.String());
  args.set_value(value);
  args.set_ttl(ttl);
  args.set_publish(publish);
  ContactInfo *sender_info = args.mutable_sender_info();
  *sender_info = info_;
  rpcprotocol::Channel *channel;
//   if (has_transport_)
//     channel = new rpcprotocol::Channel(channel_manager_, transport_, ip,
//                                        port, "", 0, rendezvous_ip,
//                                        rendezvous_port);
//   else
    channel = new rpcprotocol::Channel(channel_manager_, ip, port,
                                       rendezvous_ip, rendezvous_port);
  KademliaService::Stub service(channel);
  service.Store(ctler, &args, resp, callback);
  delete channel;
}

void KadRpcs::Downlist(const std::vector<std::string> downlist,
                       const IP &ip, const Port &port, const IP &rendezvous_ip,
                       const Port &rendezvous_port, DownlistResponse *resp,
                       rpcprotocol::Controller *ctler,
                       google::protobuf::Closure *callback) {
  DownlistRequest args;
  for (unsigned int i = 0; i < downlist.size(); ++i)
    args.add_downlist(downlist[i]);
  rpcprotocol::Controller controller;
  ContactInfo *sender_info = args.mutable_sender_info();
  *sender_info = info_;
  rpcprotocol::Channel *channel;
//   if (has_transport_)
//     channel = new rpcprotocol::Channel(channel_manager_, transport_, ip,
//                                        port, "", 0, rendezvous_ip,
//                                        rendezvous_port);
//   else
    channel = new rpcprotocol::Channel(channel_manager_, ip, port,
                                       rendezvous_ip, rendezvous_port);
  KademliaService::Stub service(channel);
  service.Downlist(ctler, &args, resp, callback);
  delete channel;
}

void KadRpcs::Bootstrap(const KadId &local_id, const IP &local_ip,
                        const Port &local_port, const IP &remote_ip,
                        const Port &remote_port, const NodeType &type,
                        BootstrapResponse *resp, rpcprotocol::Controller *ctler,
                        google::protobuf::Closure *callback) {
  BootstrapRequest args;
  args.set_newcomer_id(local_id.String());
  args.set_newcomer_local_ip(local_ip);
  args.set_newcomer_local_port(local_port);
  args.set_node_type(type);
  rpcprotocol::Channel *channel;
//   if (has_transport_)
//     channel = new rpcprotocol::Channel(channel_manager_, transport_,
//                                        remote_ip, remote_port, "", 0, "", 0);
//   else
    channel = new rpcprotocol::Channel(channel_manager_, remote_ip,
                                       remote_port, "", 0);
  KademliaService::Stub service(channel);
  service.Bootstrap(ctler, &args, resp, callback);
  delete channel;
}

void KadRpcs::Delete(const KadId &key, const SignedValue &value,
                     const SignedRequest &sig_req, const IP &ip,
                     const Port &port, const IP &rendezvous_ip,
                     const Port &rendezvous_port, DeleteResponse *resp,
                     rpcprotocol::Controller *ctler,
                     google::protobuf::Closure *callback) {
  DeleteRequest args;
  args.set_key(key.String());
  SignedValue *svalue = args.mutable_value();
  *svalue = value;
  SignedRequest *sreq = args.mutable_signed_request();
  *sreq = sig_req;
  ContactInfo *sender_info = args.mutable_sender_info();
  *sender_info = info_;
  rpcprotocol::Channel *channel;
//   if (has_transport_)
//     channel = new rpcprotocol::Channel(channel_manager_, transport_, ip,
//                                        port, "", 0, rendezvous_ip,
//                                        rendezvous_port);
//   else
    channel = new rpcprotocol::Channel(channel_manager_, ip, port,
                                       rendezvous_ip, rendezvous_port);
  KademliaService::Stub service(channel);
  service.Delete(ctler, &args, resp, callback);
  delete channel;
}

void KadRpcs::Update(const KadId &key, const SignedValue &new_value,
                     const SignedValue &old_value, const boost::int32_t &ttl,
                     const SignedRequest &sig_req, const IP &ip,
                     const Port &port, const IP &rendezvous_ip,
                     const Port &rendezvous_port, UpdateResponse *resp,
                     rpcprotocol::Controller *ctler,
                     google::protobuf::Closure *callback) {
  UpdateRequest args;
  args.set_key(key.String());
  SignedValue *newvalue = args.mutable_new_value();
  *newvalue = new_value;
  SignedValue *oldvalue = args.mutable_old_value();
  *oldvalue = old_value;
  args.set_ttl(ttl);
  SignedRequest *sreq = args.mutable_request();
  *sreq = sig_req;
  ContactInfo *sender_info = args.mutable_sender_info();
  *sender_info = info_;
  rpcprotocol::Channel *channel;
//   if (has_transport_)
//     channel = new rpcprotocol::Channel(channel_manager_, transport_, ip,
//                                        port, "", 0, rendezvous_ip,
//                                        rendezvous_port);
//   else
    channel = new rpcprotocol::Channel(channel_manager_, ip, port,
                                       rendezvous_ip, rendezvous_port);
  KademliaService::Stub service(channel);
  service.Update(ctler, &args, resp, callback);
  delete channel;
}

}  // namespace kademlia