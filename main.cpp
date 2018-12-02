#include "Client/Connection.h"
#include <IO/WriteBufferFromFileDescriptor.h>
#include <Interpreters/Context.h>
#include <iostream>


static std::shared_ptr<DB::IBlockOutputStream> block_out_stream;

bool receiveResponse(
        const DB::Context & context,
        DB::WriteBufferFromFileDescriptor *std_out,
        DB::Connection *connection)
{
    DB::Connection::Packet packet = connection->receivePacket();

    switch (packet.type)
    {
        case DB::Protocol::Server::Data:

            if (packet.block) {
                std::cerr << packet.block.rows() << " Data Rows!" << std::endl;

                if (!block_out_stream) {
                    block_out_stream = context.getOutputFormat("JSONEachRow", *std_out, packet.block);
                    block_out_stream->writePrefix();
                }

                if (packet.block.rows() != 0)
                {
                    block_out_stream->write(packet.block);
                }

                block_out_stream->flush();
            } else {
                std::cerr << "Empty Data!" << std::endl;
            }

            return true;

        case DB::Protocol::Server::Progress:
            std::cerr << "Progress!" << std::endl;
            return true;

        case DB::Protocol::Server::ProfileInfo:
            std::cerr << "ProfileInfo!" << std::endl;
            return true;

        case DB::Protocol::Server::Totals:
            std::cerr << "Totals!" << std::endl;
            return true;

        case DB::Protocol::Server::Extremes:
            std::cerr << "Extremes!" << std::endl;
            return true;

        case DB::Protocol::Server::Exception:
            std::cerr << "Exception!" << std::endl;
            return true;

        case DB::Protocol::Server::Log:
            std::cerr << "Log!" << std::endl;
            break;

        case DB::Protocol::Server::EndOfStream:
            std::cerr << "EndOfStream!" << std::endl;
            return false;

        default:
            std::cerr << "StreamError!" << std::endl;
    }

    return false;
}

int main() {
    DB::Context context = DB::Context::createGlobal();
    DB::WriteBufferFromFileDescriptor std_out(STDOUT_FILENO);

    DB::ConnectionTimeouts timeouts(
            Poco::Timespan(5, 0),
            Poco::Timespan(5, 0),
            Poco::Timespan(5, 0));

    DB::Connection connection("127.0.0.1", 9000, "", "default", "", timeouts);
    connection.sendQuery("SELECT 1+1");

    while (receiveResponse(context, &std_out, &connection)) {}

    return 0;
}