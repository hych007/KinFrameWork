//
// Created by Kin on 2018/9/23 0023.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#ifndef KINBASE_KINEXCEPTION_H
#define KINBASE_KINEXCEPTION_H

#include <exception>
#include <string_view>
#include <boost/signals2/signal.hpp>

#include "KinCodeInfo.h"


namespace KinBase
{
    class KinException;

    /**
     * @brief
     * @date 2018/9/23 0023
     * @author Kin
     * @copyright Copyright © 2018 jihuisoft. All rights reserved.
     */
    class KinException
        : public std::exception, public KinCodeInfo
    {
    public:
        using KinCodeInfo::KinCodeInfo;
        using HandlerType = boost::signals2::signal<int(KinBase::KinException&)>;

        explicit KinException(const KinCodeInfo &Info);

        const char *what() const noexcept override;

        static HandlerType& GetExceptionHandler();

        template<typename eType>
        static int Throw(const KinBase::KinCodeInfo &) noexcept(false);
    };

    class MustException
        : public KinBase::KinException
    {
    public:
        using KinException::KinException;
    };

    class ShouldException
        : public KinBase::KinException
    {
    public:
        using KinException::KinException;
    };

#define Must(Condition, ...)                                               \
(!!(Condition))?0:KinBase::KinException::Throw<KinBase::MustException>(    \
MakeCodeInfo(#Condition,##__VA_ARGS__))

#define Should(Condition, ...)                                             \
(!!(Condition))?0:KinBase::KinException::Throw<KinBase::ShouldException>(  \
MakeCodeInfo(#Condition,##__VA_ARGS__))

}


#endif //KINBASE_KINEXCEPTION_H
