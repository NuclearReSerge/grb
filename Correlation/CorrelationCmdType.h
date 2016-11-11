#pragma once

namespace grb
{
namespace type
{

enum CorrelationCmdType
{
  CORRELATION_CREATE,
  CORRELATION_HELP,

  CORRELATION_GENERATE,
  CORRELATION_SAVE,

  CORRELATION_SET_XAXIS,
  CORRELATION_SET_YAXIS,
  CORRELATION_SET_FILEPREFIX,

  // LAST
  UNDEFINED_CORRELATION_CMD
};

} // namespace type
} // namespace grb
