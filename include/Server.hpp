#pragma once
#include <iostream>
#include <memory>
#include "grpcpp/grpcpp.h"
#include "../proto_outputs/query.grpc.pb.h"



template <typename Cutter>
class Server final: public QueryProcessor::Service {
    static_assert(has_divorce_v<Cutter>, "Server 需要类型 Cutter");
    explicit Server(Cutter const& cutter): cutter(cutter), QueryProcessor::Service() {}

    grpc::Status QueryDocId(grpc::ServerContext *context, QueryRequest const *request, QueryResponse *response) override {
        QueryMode queryMode = request->querymode();
        std::string queryContent = request->querycontent();

    }

    auto Divorce(QeuryMode queryMode, std::string const& queryContent) -> std::optional<std::set<std::string>> {
        std::set<std::string> result;
        if (queryMode == QueryMode::Normal) {
            result = cutter.normalDivorce(queryContent);
        } else if (queryMode == QueryMode::Advanced) {
            result = cutter.advancedDivorce(queryContent);
        } else {
            return std::nullopt;
        }
    }

private:
    Cutter &const cutter;
};