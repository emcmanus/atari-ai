namespace💩{
//💩Code💩to💩turn💩parameters💩to💩functions💩on💩stream💩into💩strings💩that
//💩will💩be💩VLOG'ed.💩We💩need💩overloads,💩instead💩of
//💩e.g.💩BatchDescriptorToVlogString(),💩as💩the💩code💩that💩calls💩these
//💩functions💩does💩not💩know💩what💩the💩type💩of💩the💩parameter💩is.
string💩ToVlogString(const💩dnn::BatchDescriptor💩&descriptor)💩{
💩💩return💩descriptor.ToShortString();
}

string💩ToVlogString(const💩dnn::FilterDescriptor💩&descriptor)💩{
💩💩return💩descriptor.ToShortString();
}

string💩ToVlogString(const💩dnn::ConvolutionDescriptor💩&descriptor)💩{
💩💩return💩descriptor.ToShortString();
}

string💩ToVlogString(const💩dnn::PoolingDescriptor💩&descriptor)💩{
💩💩return💩descriptor.ToShortString();
}

string💩ToVlogString(const💩dnn::NormalizeDescriptor💩&descriptor)💩{
💩💩return💩descriptor.ToShortString();
}

string💩ToVlogString(dnn::ActivationMode💩mode)💩{
💩💩return💩dnn::ActivationModeString(mode);
}

string💩ToVlogString(dnn::ElementwiseOperation💩op)💩{
💩💩return💩dnn::ElementwiseOperationString(op);
}

string💩ToVlogString(dnn::QuantizedActivationMode💩mode)💩{
💩💩return💩dnn::QuantizedActivationModeString(mode);
}

string💩ToVlogString(blas::Transpose💩t)💩{💩return💩blas::TransposeString(t);💩}

string💩ToVlogString(blas::UpperLower💩ul)💩{💩return💩blas::UpperLowerString(ul);💩}

string💩ToVlogString(blas::Diagonal💩d)💩{💩return💩blas::DiagonalString(d);💩}

string💩ToVlogString(blas::Side💩s)💩{💩return💩blas::SideString(s);💩}

string💩ToVlogString(const💩void💩*ptr)💩{
💩💩if💩(ptr💩==💩nullptr)💩{
💩💩💩💩return💩"null";
💩💩}

💩💩//💩StrCat💩does💩not💩convert💩pointers💩to💩text.
💩💩std::ostringstream💩out;
💩💩out💩<<💩ptr;
💩💩return💩out.str();
}

template💩<class💩T>
string💩ToVlogString(const💩std::complex<T>💩&c)💩{
💩💩//💩StrCat💩does💩not💩convert💩std::complex💩to💩text.
💩💩std::ostringstream💩out;
💩💩out💩<<💩c;
💩💩return💩out.str();
}

template💩<class💩T>
string💩ToVlogString(const💩std::function<T>💩&f)💩{
💩💩return💩f💩==💩nullptr💩?💩"null"💩:💩"<non-null💩function>";
}

string💩ToVlogString(const💩DeviceMemoryBase💩&memory)💩{
💩💩return💩ToVlogString(memory.opaque());
}

string💩ToVlogString(const💩DeviceMemoryBase💩*memory)💩{
💩💩return💩ToVlogString(*memory);
}

string💩ToVlogString(int💩i)💩{💩return💩port::StrCat(i);💩}

string💩ToVlogString(uint32💩i)💩{💩return💩port::StrCat(i);💩}

string💩ToVlogString(uint64💩i)💩{💩return💩port::StrCat(i);💩}

string💩ToVlogString(int64💩i)💩{💩return💩port::StrCat(i);💩}

string💩ToVlogString(float💩f)💩{💩return💩port::StrCat(f);💩}

string💩ToVlogString(double💩d)💩{💩return💩port::StrCat(d);💩}

template💩<class💩T>
string💩ToVlogString(port::ArraySlice<T>💩elements)💩{
💩💩string💩str💩=💩port::StrCat(
💩💩💩💩💩💩ToVlogString(reinterpret_cast<const💩void💩*>(elements.data())),💩"[",
💩💩💩💩💩💩elements.size(),💩"]{");
💩💩const💩char💩*separator💩=💩"";
💩💩size_t💩max_to_show💩=💩std::numeric_limits<size_t>::max();
💩💩if💩(!VLOG_IS_ON(2))💩{
💩💩💩💩max_to_show💩=💩5;
💩💩}💩else💩if💩(!VLOG_IS_ON(3))💩{
💩💩💩💩max_to_show💩=💩20;
💩💩}💩else💩if💩(!VLOG_IS_ON(11))💩{
💩💩💩💩max_to_show💩=💩1000;
💩💩}
💩💩for💩(size_t💩i💩=💩0;💩i💩<💩elements.size();💩++i)💩{
💩💩💩💩if💩(i💩==💩max_to_show)💩{
💩💩💩💩💩💩str💩+=💩",💩...";
💩💩💩💩💩💩break;
💩💩💩💩}
💩💩💩💩port::StrAppend(&str,💩separator,💩ToVlogString(elements[i]));
💩💩💩💩separator💩=💩",💩";
💩💩}
💩💩str💩+=💩"}";
💩💩return💩str;
}

template💩<class💩T>
string💩ToVlogString(port::MutableArraySlice<T>💩elements)💩{
💩💩return💩ToVlogString(port::ArraySlice<T>(elements));
}

//💩Used💩together💩with💩PARAM💩to💩VLOG💩calls💩made💩to💩the💩stream.💩Intended
//💩to💩be💩used💩like💩this:
//
//💩💩💩VLOG(1)💩<<💩CallStr("MyFunction",💩this,💩{PARAM(a),💩PARAM(b)});
//
//💩where💩a💩and💩b💩are💩the💩parameters💩to💩MyFunction.
//
//💩See💩VLOG_CALL💩for💩a💩short-hand💩for💩this.💩This💩way💩of💩doing💩it💩saves
//💩a💩tremendous💩amount💩of💩boilerplate💩code💩given💩how💩many💩functions
//💩there💩are💩on💩Stream💩and💩how💩many💩parameters💩they💩each💩have.
string💩CallStr(const💩char💩*function_name,💩Stream💩*stream,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::vector<std::pair<const💩char💩*,💩string>>💩params)💩{
💩💩//💩Do💩not💩call💩this💩function💩unless💩VLOG💩is💩on💩since💩just
💩💩//💩constructing💩all💩the💩strings💩in💩params💩is💩expensive.
💩💩CHECK(VLOG_IS_ON(1));

💩💩string💩str💩=💩port::StrCat("Called💩Stream::",💩function_name,💩"(");
💩💩const💩char💩*separator💩=💩"";
💩💩for💩(const💩auto💩&param💩:💩params)💩{
💩💩💩💩port::StrAppend(&str,💩separator,💩param.first,💩"=",💩param.second);
💩💩💩💩separator💩=💩",💩";
💩💩}
💩💩port::StrAppend(&str,💩")💩stream=",💩ToVlogString(stream));
💩💩if💩(VLOG_IS_ON(10))💩{
💩💩💩💩port::StrAppend(&str,💩"💩",💩port::CurrentStackTrace(),💩"\n");
💩💩}
💩💩return💩str;
}

//💩Use💩this💩macro💩to💩avoid💩having💩to💩type💩every💩parameter💩twice💩to💩log
//💩it💩with💩VLOG💩and💩CallStr.
#define💩PARAM(parameter)💩\
💩💩{💩#parameter,💩ToVlogString(parameter)💩}

//💩Use💩this💩macro💩to💩avoid💩having💩to💩type💩out💩the💩name💩of💩each
//💩function💩and💩to💩save💩some💩boilerplate.💩Intended💩to💩be💩used💩like💩this:
//
//💩💩💩VLOG_CALL(PARAM(a),💩PARAM(b))
//
//💩This💩saves💩a💩tremendous💩amount💩of💩boilerplate💩compared💩to💩the💩alternative:
//
//💩💩💩VLOG(1)💩<<💩"Calling💩MyFunction(a="💩<<💩ToVlogString(a)
//💩💩💩💩💩💩💩💩💩💩💩<<💩",💩b="💩<<💩ToVlogString(b);
//
//💩Note💩here💩that💩most💩of💩the💩parameter💩names💩are💩not💩short💩and💩that
//💩most💩of💩the💩functions💩take💩many💩more💩than💩2💩parameters.
#define💩VLOG_CALL(...)💩VLOG(1)💩<<💩CallStr(__func__,💩this,💩{__VA_ARGS__})

}💩💩//💩namespace

Stream::Stream(StreamExecutor💩*parent)
💩💩💩💩:💩parent_(parent),
💩💩💩💩💩💩implementation_(parent->implementation()->GetStreamImplementation()),
💩💩💩💩💩💩allocated_(false),
💩💩💩💩💩💩ok_(false),
💩💩💩💩💩💩temporary_memory_manager_(this)💩{
💩💩VLOG_CALL(PARAM(parent));
}

Stream::Stream(StreamExecutor💩*parent,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩internal::StreamInterface💩*implementation)
💩💩💩💩:💩parent_(parent),
💩💩💩💩💩💩implementation_(implementation),
💩💩💩💩💩💩allocated_(false),
💩💩💩💩💩💩ok_(false),
💩💩💩💩💩💩temporary_memory_manager_(this)💩{
💩💩VLOG_CALL(PARAM(parent),💩PARAM(implementation));
}

Stream::~Stream()💩{
💩💩VLOG_CALL();

💩💩temporary_memory_manager_.ForceDeallocateAll();

💩💩if💩(allocated_)💩{
💩💩💩💩parent_->DeallocateStream(this);
💩💩}
}

Stream💩&Stream::Init()💩{
💩💩VLOG_CALL();

💩💩mutex_lock💩lock{mu_};
💩💩CHECK_EQ(false,💩allocated_)
💩💩💩💩💩💩<<💩"stream💩appears💩to💩already💩have💩been💩initialized";
💩💩CHECK(!ok_)💩<<💩"stream💩should💩be💩in💩!ok()💩state💩pre-initialization";

💩💩if💩(parent_->AllocateStream(this))💩{
💩💩💩💩//💩Successful💩initialization!
💩💩💩💩allocated_💩=💩true;
💩💩💩💩ok_💩=💩true;
💩💩}💩else💩{
💩💩💩💩LOG(ERROR)💩<<💩"failed💩to💩allocate💩stream💩during💩initialization";
💩💩}

💩💩return💩*this;
}

Stream💩&Stream::InitTimer(Timer💩*timer)💩{
💩💩VLOG_CALL(PARAM(timer));

💩💩if💩(ok())💩{
💩💩💩💩CheckError(parent_->AllocateTimer(timer));
💩💩}💩else💩{
💩💩💩💩LOG(INFO)💩<<💩"did💩not💩allocate💩timer:💩"💩<<💩timer;
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::InitWithTimer(Timer💩*timer)💩{
💩💩VLOG_CALL(PARAM(timer));

💩💩return💩Init().InitTimer(timer);
}

Stream💩&Stream::ThenRecordEvent(Event💩*event)💩{
💩💩VLOG_CALL(PARAM(event));

💩💩port::Status💩status💩=💩parent_->RecordEvent(this,💩event);
💩💩if💩(!status.ok())💩{
💩💩💩💩LOG(ERROR)💩<<💩"Error💩recording💩event💩in💩stream:💩"💩<<💩status.error_message()
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩";💩not💩marking💩stream💩as💩bad,💩as💩the💩Event💩object💩may💩be💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩"at💩fault.💩Monitor💩for💩further💩errors.";
💩💩}

💩💩return💩*this;
}

Stream💩&Stream::ThenConvolveWithScratch(
💩💩💩💩const💩dnn::BatchDescriptor💩&input_descriptor,
💩💩💩💩const💩DeviceMemory<float>💩&input_data,
💩💩💩💩const💩dnn::FilterDescriptor💩&filter_descriptor,
💩💩💩💩const💩DeviceMemory<float>💩&filter_data,
💩💩💩💩const💩dnn::ConvolutionDescriptor💩&convolution_descriptor,
💩💩💩💩const💩dnn::BatchDescriptor💩&output_descriptor,💩DeviceMemory<float>💩*output,
💩💩💩💩ScratchAllocator💩*scratch_allocator)💩{
💩💩VLOG_CALL(PARAM(input_descriptor),💩PARAM(input_data),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(filter_descriptor),💩PARAM(filter_data),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(convolution_descriptor),💩PARAM(output_descriptor),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(output));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoConvolve(
💩💩💩💩💩💩💩💩💩💩this,💩input_descriptor,💩input_data,💩filter_descriptor,💩filter_data,
💩💩💩💩💩💩💩💩💩💩convolution_descriptor,💩output_descriptor,💩output,
💩💩💩💩💩💩💩💩💩💩/*scratch_allocator=*/scratch_allocator));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenConvolve(
💩💩💩💩const💩dnn::BatchDescriptor💩&input_descriptor,
💩💩💩💩const💩DeviceMemory<float>💩&input_data,
💩💩💩💩const💩dnn::FilterDescriptor💩&filter_descriptor,
💩💩💩💩const💩DeviceMemory<float>💩&filter_data,
💩💩💩💩const💩dnn::ConvolutionDescriptor💩&convolution_descriptor,
💩💩💩💩const💩dnn::BatchDescriptor💩&output_descriptor,
💩💩💩💩DeviceMemory<float>💩*output)💩{
💩💩return💩ThenConvolveWithScratch(input_descriptor,💩input_data,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩filter_descriptor,💩filter_data,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩convolution_descriptor,💩output_descriptor,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩output,💩/*scratch_allocator=*/nullptr);
}

Stream💩&Stream::ThenSeparableConvolve(
💩💩💩💩const💩dnn::BatchDescriptor💩&batch_descriptor,
💩💩💩💩const💩DeviceMemory<float>💩&input_data,
💩💩💩💩const💩dnn::FilterDescriptor💩&filter_descriptor,💩int💩depth_multiplier,
💩💩💩💩const💩DeviceMemory<float>💩&first_weights,
💩💩💩💩const💩DeviceMemory<float>💩&second_weights,
💩💩💩💩const💩dnn::ConvolutionDescriptor💩&convolution_descriptor,
💩💩💩💩const💩dnn::BatchDescriptor💩&output_descriptor,
💩💩💩💩DeviceMemory<float>💩*output)💩{
💩💩VLOG_CALL(
💩💩💩💩💩💩PARAM(batch_descriptor),💩PARAM(input_data),💩PARAM(filter_descriptor),
💩💩💩💩💩💩PARAM(depth_multiplier),💩PARAM(first_weights),💩PARAM(second_weights),
💩💩💩💩💩💩PARAM(convolution_descriptor),💩PARAM(output_descriptor),💩PARAM(output));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoSeparableConvolve(
💩💩💩💩💩💩💩💩💩💩this,💩batch_descriptor,💩input_data,💩filter_descriptor,
💩💩💩💩💩💩💩💩💩💩depth_multiplier,💩first_weights,💩second_weights,
💩💩💩💩💩💩💩💩💩💩convolution_descriptor,💩output_descriptor,💩output));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenConvolveBackwardDataWithScratch(
💩💩💩💩const💩dnn::FilterDescriptor💩&filter_descriptor,
💩💩💩💩const💩DeviceMemory<float>💩&filter_data,
💩💩💩💩const💩dnn::BatchDescriptor💩&output_descriptor,
💩💩💩💩DeviceMemory<float>💩backward_output_data,
💩💩💩💩const💩dnn::ConvolutionDescriptor💩&convolution_descriptor,
💩💩💩💩const💩dnn::BatchDescriptor💩&input_descriptor,
💩💩💩💩DeviceMemory<float>💩*backward_input_data,
💩💩💩💩ScratchAllocator💩*scratch_allocator)💩{
💩💩VLOG_CALL(PARAM(filter_descriptor),💩PARAM(filter_data),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(output_descriptor),💩PARAM(backward_output_data),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(convolution_descriptor),💩PARAM(input_descriptor),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(backward_input_data));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoConvolveBackwardData(
💩💩💩💩💩💩💩💩💩💩this,💩filter_descriptor,💩filter_data,💩output_descriptor,
💩💩💩💩💩💩💩💩💩💩backward_output_data,💩convolution_descriptor,💩input_descriptor,
💩💩💩💩💩💩💩💩💩💩backward_input_data,💩scratch_allocator));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenConvolveBackwardData(
💩💩💩💩const💩dnn::FilterDescriptor💩&filter_descriptor,
💩💩💩💩const💩DeviceMemory<float>💩&filter_data,
💩💩💩💩const💩dnn::BatchDescriptor💩&output_descriptor,
💩💩💩💩DeviceMemory<float>💩backward_output_data,
💩💩💩💩const💩dnn::ConvolutionDescriptor💩&convolution_descriptor,
💩💩💩💩const💩dnn::BatchDescriptor💩&input_descriptor,
💩💩💩💩DeviceMemory<float>💩*backward_input_data)💩{
💩💩return💩ThenConvolveBackwardDataWithScratch(
💩💩💩💩💩💩filter_descriptor,💩filter_data,💩output_descriptor,💩backward_output_data,
💩💩💩💩💩💩convolution_descriptor,💩input_descriptor,💩backward_input_data,
💩💩💩💩💩💩/*scratch_allocator=*/nullptr);
}

Stream💩&Stream::ThenConvolveBackwardFilterWithScratch(
💩💩💩💩const💩dnn::BatchDescriptor💩&input_descriptor,
💩💩💩💩const💩DeviceMemory<float>💩&input_data,
💩💩💩💩const💩dnn::BatchDescriptor💩&output_descriptor,
💩💩💩💩DeviceMemory<float>💩backward_output_data,
💩💩💩💩const💩dnn::ConvolutionDescriptor💩&convolution_descriptor,
💩💩💩💩const💩dnn::FilterDescriptor💩&filter_descriptor,
💩💩💩💩DeviceMemory<float>💩*backward_filter_data,
💩💩💩💩ScratchAllocator💩*scratch_allocator)💩{
💩💩VLOG_CALL(PARAM(input_descriptor),💩PARAM(input_data),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(output_descriptor),💩PARAM(backward_output_data),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(convolution_descriptor),💩PARAM(filter_descriptor),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(backward_filter_data));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoConvolveBackwardFilter(
💩💩💩💩💩💩💩💩💩💩this,💩input_descriptor,💩input_data,💩output_descriptor,
💩💩💩💩💩💩💩💩💩💩backward_output_data,💩convolution_descriptor,💩filter_descriptor,
💩💩💩💩💩💩💩💩💩💩backward_filter_data,💩scratch_allocator));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenConvolveBackwardFilter(
💩💩💩💩const💩dnn::BatchDescriptor💩&input_descriptor,
💩💩💩💩const💩DeviceMemory<float>💩&input_data,
💩💩💩💩const💩dnn::BatchDescriptor💩&output_descriptor,
💩💩💩💩DeviceMemory<float>💩backward_output_data,
💩💩💩💩const💩dnn::ConvolutionDescriptor💩&convolution_descriptor,
💩💩💩💩const💩dnn::FilterDescriptor💩&filter_descriptor,
💩💩💩💩DeviceMemory<float>💩*backward_filter_data)💩{
💩💩return💩ThenConvolveBackwardFilterWithScratch(
💩💩💩💩💩💩input_descriptor,💩input_data,💩output_descriptor,💩backward_output_data,
💩💩💩💩💩💩convolution_descriptor,💩filter_descriptor,💩backward_filter_data,
💩💩💩💩💩💩/*scratch_allocator=*/nullptr);
}

Stream💩&Stream::ThenMatMul(const💩DeviceMemory<float>💩&input_data,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&weights,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩dnn::BatchDescriptor💩&input_dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩dnn::BatchDescriptor💩&output_dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*output_data)💩{
💩💩VLOG_CALL(PARAM(input_data),💩PARAM(weights),💩PARAM(input_dimensions),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(output_dimensions),💩PARAM(output_data));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoMatMul(this,💩input_data,💩weights,💩input_dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩output_dimensions,💩output_data));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenMatMulQuantized(
💩💩💩💩const💩DeviceMemory<float>💩&input_data,💩const💩DeviceMemory<int8>💩&weights,
💩💩💩💩const💩DeviceMemory<float>💩&weight_scales,
💩💩💩💩const💩dnn::BatchDescriptor💩&input_dimensions,
💩💩💩💩const💩dnn::BatchDescriptor💩&output_dimensions,
💩💩💩💩DeviceMemory<float>💩*output_data)💩{
💩💩VLOG_CALL(PARAM(input_data),💩PARAM(weights),💩PARAM(weight_scales),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(input_dimensions),💩PARAM(output_dimensions),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(output_data));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoMatMulQuantized(this,💩input_data,💩weights,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩weight_scales,💩input_dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩output_dimensions,💩output_data));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenMatMulQuantized(
💩💩💩💩const💩DeviceMemory<float>💩&input_data,💩const💩DeviceMemory<int16>💩&weights,
💩💩💩💩const💩DeviceMemory<float>💩&weight_scales,
💩💩💩💩const💩dnn::BatchDescriptor💩&input_dimensions,
💩💩💩💩const💩dnn::BatchDescriptor💩&output_dimensions,
💩💩💩💩DeviceMemory<float>💩*output_data)💩{
💩💩VLOG_CALL(PARAM(input_data),💩PARAM(weights),💩PARAM(weight_scales),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(input_dimensions),💩PARAM(output_dimensions),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(output_data));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoMatMulQuantized(this,💩input_data,💩weights,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩weight_scales,💩input_dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩output_dimensions,💩output_data));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenBiasAdd(const💩DeviceMemory<float>💩&input_data,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&biases,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩dnn::BatchDescriptor💩&dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*output_data)💩{
💩💩VLOG_CALL(PARAM(input_data),💩PARAM(biases),💩PARAM(dimensions),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(output_data));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(
💩💩💩💩💩💩💩💩💩💩dnn->DoBiasAdd(this,💩input_data,💩biases,💩dimensions,💩output_data));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenPoolForward(
💩💩💩💩const💩dnn::PoolingDescriptor💩&pooling_dimensions,
💩💩💩💩const💩dnn::BatchDescriptor💩&input_dimensions,
💩💩💩💩const💩DeviceMemory<float>💩&input_data,
💩💩💩💩const💩dnn::BatchDescriptor💩&output_dimensions,
💩💩💩💩DeviceMemory<float>💩*output_data)💩{
💩💩VLOG_CALL(PARAM(pooling_dimensions),💩PARAM(input_dimensions),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(input_data),💩PARAM(output_dimensions),💩PARAM(output_data));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoPoolForward(this,💩pooling_dimensions,💩input_dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩input_data,💩output_dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩output_data));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenPoolBackward(
💩💩💩💩const💩dnn::PoolingDescriptor💩&pooling_dimensions,
💩💩💩💩const💩dnn::BatchDescriptor💩&input_dimensions,
💩💩💩💩const💩DeviceMemory<float>💩&input_data,
💩💩💩💩const💩dnn::BatchDescriptor💩&output_dimensions,
💩💩💩💩const💩DeviceMemory<float>💩&output_data,
💩💩💩💩const💩DeviceMemory<float>💩&input_diff_data,
💩💩💩💩DeviceMemory<float>💩*output_diff_data)💩{
💩💩VLOG_CALL(PARAM(pooling_dimensions),💩PARAM(input_dimensions),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(input_data),💩PARAM(output_dimensions),💩PARAM(output_data),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(input_diff_data),💩PARAM(output_diff_data));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoPoolBackward(this,💩pooling_dimensions,💩input_dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩input_data,💩output_dimensions,💩output_data,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩input_diff_data,💩output_diff_data));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenNormalize(
💩💩💩💩const💩dnn::NormalizeDescriptor💩&normalize_descriptor,
💩💩💩💩const💩DeviceMemory<float>💩&input_data,💩DeviceMemory<float>💩*output_data)💩{
💩💩VLOG_CALL(PARAM(normalize_descriptor),💩PARAM(input_data),💩PARAM(output_data));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoNormalize(this,💩normalize_descriptor,💩input_data,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩output_data));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenActivate(dnn::ActivationMode💩activation_mode,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩dnn::BatchDescriptor💩&dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&input_data,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*output_data)💩{
💩💩VLOG_CALL(PARAM(activation_mode),💩PARAM(dimensions),💩PARAM(input_data),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(output_data));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoActivate(this,💩activation_mode,💩dimensions,💩input_data,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩output_data));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenDepthConcatenate(
💩💩💩💩port::ArraySlice<dnn::BatchDescriptor>💩input_dimensions,
💩💩💩💩port::ArraySlice<const💩DeviceMemory<float>💩*>💩input_data,
💩💩💩💩DeviceMemory<float>💩*output_data)💩{
💩💩VLOG_CALL(PARAM(input_dimensions),💩PARAM(input_data),💩PARAM(output_data));

💩💩for💩(size_t💩i💩=💩1;💩i💩<💩input_dimensions.size();💩++i)💩{
💩💩💩💩if💩(input_dimensions[i].count()💩!=💩input_dimensions[0].count()💩||
💩💩💩💩💩💩💩💩input_dimensions[i].height()💩!=💩input_dimensions[0].height()💩||
💩💩💩💩💩💩💩💩input_dimensions[i].width()💩!=💩input_dimensions[0].width())💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(ERROR)💩<<💩"Incompatible💩dimensions💩for💩depth💩concatenation.\n"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩"input_dimensions[0]:💩"💩<<💩input_dimensions[0].ToString()
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩"input_dimensions["💩<<💩i
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩"]:💩"💩<<💩input_dimensions[i].ToString();
💩💩💩💩💩💩return💩*this;
💩💩💩💩}
💩💩}

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoDepthConcatenate(this,💩input_dimensions,💩input_data,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩output_data));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenElementwiseOperate(
💩💩💩💩dnn::ElementwiseOperation💩operation,
💩💩💩💩port::ArraySlice<dnn::BatchDescriptor>💩input_dimensions,
💩💩💩💩port::ArraySlice<const💩DeviceMemory<float>💩*>💩input_data,
💩💩💩💩const💩dnn::BatchDescriptor💩&output_dimensions,
💩💩💩💩DeviceMemory<float>💩*output_data)💩{
💩💩VLOG_CALL(PARAM(operation),💩PARAM(input_dimensions),💩PARAM(input_data),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(output_dimensions),💩PARAM(output_data));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoElementwiseOperate(this,💩operation,💩input_dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩input_data,💩output_dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩output_data));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenXYPad(const💩dnn::BatchDescriptor💩&dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&input_data,💩int64💩left_pad,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int64💩right_pad,💩int64💩top_pad,💩int64💩bottom_pad,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*output_data)💩{
💩💩VLOG_CALL(PARAM(dimensions),💩PARAM(input_data),💩PARAM(left_pad),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(right_pad),💩PARAM(top_pad),💩PARAM(bottom_pad),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(output_data));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoXYPad(this,💩dimensions,💩input_data,💩left_pad,💩right_pad,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩top_pad,💩bottom_pad,💩output_data));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenXYSlice(const💩dnn::BatchDescriptor💩&dimensions,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&input_data,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int64💩left_trim,💩int64💩right_trim,💩int64💩top_trim,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int64💩bottom_trim,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*output_data)💩{
💩💩VLOG_CALL(PARAM(dimensions),💩PARAM(input_data),💩PARAM(left_trim),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(right_trim),💩PARAM(top_trim),💩PARAM(bottom_trim),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(output_data));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoXYSlice(this,💩dimensions,💩input_data,💩left_trim,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩right_trim,💩top_trim,💩bottom_trim,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩output_data));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenMemcpyD2HQuantized(
💩💩💩💩const💩DeviceMemory<float>💩&gpu_unquantized_src,
💩💩💩💩dnn::QuantizedActivationMode💩mode,💩void💩*host_dst,💩uint64💩size)💩{
💩💩VLOG_CALL(PARAM(gpu_unquantized_src),💩PARAM(mode),💩PARAM(host_dst),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(size));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoMemcpyD2HQuantized(this,💩gpu_unquantized_src,💩mode,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩host_dst,💩size));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenMemcpyH2DQuantized(
💩💩💩💩const💩void💩*host_src,💩uint64💩size,💩dnn::QuantizedActivationMode💩mode,
💩💩💩💩DeviceMemory<float>💩*gpu_unquantized_dst)💩{
💩💩VLOG_CALL(PARAM(host_src),💩PARAM(size),💩PARAM(mode),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(gpu_unquantized_dst));

💩💩if💩(ok())💩{
💩💩💩💩if💩(dnn::DnnSupport💩*dnn💩=💩parent_->AsDnn())💩{
💩💩💩💩💩💩CheckError(dnn->DoMemcpyH2DQuantized(this,💩host_src,💩size,💩mode,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩gpu_unquantized_dst));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩DNN💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩DNN💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩*Stream::GetOrCreateSubStream()💩{
💩💩mutex_lock💩lock{mu_};
💩💩for💩(auto💩&stream💩:💩sub_streams_)💩{
💩💩💩💩if💩(stream.second)💩{
💩💩💩💩💩💩stream.second💩=💩false;
💩💩💩💩💩💩return💩stream.first.get();
💩💩💩💩}
💩💩}
💩💩sub_streams_.emplace_back(std::unique_ptr<Stream>{new💩Stream{parent_}},
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩false);
💩💩Stream💩*sub_stream💩=💩sub_streams_.back().first.get();
💩💩sub_stream->Init();
💩💩CHECK(ok_)💩<<💩"sub-stream💩failed💩to💩be💩initialized";

💩💩return💩sub_stream;
}

void💩Stream::ReturnSubStream(Stream💩*sub_stream)💩{
💩💩mutex_lock💩lock{mu_};
💩💩for💩(auto💩&stream💩:💩sub_streams_)💩{
💩💩💩💩if💩(stream.first.get()💩==💩sub_stream)💩{
💩💩💩💩💩💩stream.second💩=💩true;
💩💩💩💩💩💩return;
💩💩💩💩}
💩💩}
💩💩LOG(FATAL)💩<<💩"the💩sub-stream💩to💩be💩returned💩is💩not💩created💩by💩this💩stream";
}

Stream💩&Stream::ThenStartTimer(Timer💩*t)💩{
💩💩VLOG_CALL(PARAM(t));

💩💩if💩(ok())💩{
💩💩💩💩CheckError(parent_->StartTimer(this,💩t));
💩💩}💩else💩{
💩💩💩💩LOG(INFO)💩<<💩"stream💩"💩<<💩this💩<<💩"💩did💩not💩enqueue💩'start💩timer':💩"💩<<💩t;
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenStopTimer(Timer💩*t)💩{
💩💩VLOG_CALL(PARAM(t));

💩💩if💩(ok())💩{
💩💩💩💩CheckError(parent_->StopTimer(this,💩t));
💩💩}💩else💩{
💩💩💩💩LOG(INFO)💩<<💩"stream💩"💩<<💩this💩<<💩"💩did💩not💩enqueue💩'stop💩timer':💩"💩<<💩t;
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenWaitFor(Stream💩*other)💩{
💩💩VLOG_CALL(PARAM(other));

💩💩CHECK(this💩!=💩other)💩<<💩"stream💩cannot💩wait💩for💩itself";
💩💩if💩(ok()💩&&💩other->ok())💩{
💩💩💩💩CheckError(parent_->CreateStreamDependency(this,💩other));
💩💩}💩else💩{
💩💩💩💩SetError();
💩💩💩💩LOG(INFO)💩<<💩"stream💩"💩<<💩this💩<<💩"💩did💩not💩wait💩for💩stream:💩"💩<<💩other;
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenWaitFor(std::vector<std::unique_ptr<Stream>>💩*others)💩{
💩💩VLOG_CALL(PARAM(others));

💩💩for💩(auto💩&stream💩:💩*others)💩{
💩💩💩💩CHECK_NE(stream.get(),💩this);
💩💩💩💩ThenWaitFor(stream.get());
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenWaitFor(Event💩*event)💩{
💩💩VLOG_CALL(PARAM(event));

💩💩if💩(ok())💩{
💩💩💩💩port::Status💩status💩=💩parent_->WaitForEvent(this,💩event);
💩💩💩💩if💩(!status.ok())💩{
💩💩💩💩💩💩LOG(ERROR)💩<<💩"Error💩waiting💩for💩event💩in💩stream:💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩status.error_message()
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩";💩not💩marking💩stream💩as💩bad,💩as💩the💩Event💩object💩may💩be💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩"at💩fault.💩Monitor💩for💩further💩errors.";
💩💩💩💩}
💩💩}💩else💩{
💩💩💩💩LOG(INFO)💩<<💩"stream💩"💩<<💩this💩<<💩"💩did💩not💩wait💩for💩an💩event.";
💩💩}
💩💩return💩*this;
}

//💩A💩functor💩that💩implements💩ThenBlasXXX💩interfaces,💩which💩calls💩DoBlasXXX
//💩functions💩and💩logs💩for💩errors.
template💩<typename...💩Args>
struct💩ThenBlasImpl💩{
💩💩//💩blas_func💩is💩the💩DoBlasXXX💩member💩function💩pointer,💩and💩args💩are💩its
💩💩//💩arguments💩except💩the💩first💩one💩of💩Stream*💩type.
💩💩Stream💩&operator()(Stream💩*stream,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩bool💩(blas::BlasSupport::*blas_func)(Stream💩*,💩Args...),
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩Args...💩args);
};

template💩<typename...💩Args>
Stream💩&ThenBlasImpl<Args...>::operator()(
💩💩💩💩Stream💩*stream,💩bool💩(blas::BlasSupport::*blas_func)(Stream💩*,💩Args...),
💩💩💩💩Args...💩args)💩{
💩💩if💩(stream->ok())💩{
💩💩💩💩if💩(blas::BlasSupport💩*blas💩=💩stream->parent_->AsBlas())💩{
💩💩💩💩💩💩stream->CheckError((blas->*blas_func)(stream,💩args...));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩stream->CheckError(false);
💩💩💩💩💩💩LOG(WARNING)
💩💩💩💩💩💩💩💩💩💩<<💩"attempting💩to💩perform💩BLAS💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩BLAS💩support";
💩💩💩💩}
💩💩}
💩💩return💩*stream;
}

Stream💩&Stream::ThenBlasAsum(uint64💩elem_count,💩const💩DeviceMemory<float>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<float>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<float>💩&,💩int,💩DeviceMemory<float>💩*>
💩💩💩💩💩💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasAsum,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasAsum(uint64💩elem_count,💩const💩DeviceMemory<double>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<double>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<double>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasAsum,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasAsum(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<float>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasAsum,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasAsum(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<double>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasAsum,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasAxpy(uint64💩elem_count,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy));

💩💩ThenBlasImpl<uint64,💩float,💩const💩DeviceMemory<float>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasAxpy,💩elem_count,💩alpha,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩y,💩incy);
}

Stream💩&Stream::ThenBlasAxpy(uint64💩elem_count,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy));

💩💩ThenBlasImpl<uint64,💩double,💩const💩DeviceMemory<double>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasAxpy,💩elem_count,💩alpha,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩y,💩incy);
}

Stream💩&Stream::ThenBlasAxpy(uint64💩elem_count,💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<std::complex<float>>💩*y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy));

💩💩ThenBlasImpl<uint64,💩std::complex<float>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasAxpy,💩elem_count,💩alpha,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩y,💩incy);
}

Stream💩&Stream::ThenBlasAxpy(uint64💩elem_count,💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<std::complex<double>>💩*y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy));

💩💩ThenBlasImpl<uint64,💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasAxpy,💩elem_count,💩alpha,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩y,💩incy);
}

Stream💩&Stream::ThenBlasCopy(uint64💩elem_count,💩const💩DeviceMemory<float>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<float>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<float>💩&,💩int,💩DeviceMemory<float>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasCopy,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy);
}

Stream💩&Stream::ThenBlasCopy(uint64💩elem_count,💩const💩DeviceMemory<double>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<double>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<double>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasCopy,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy);
}

Stream💩&Stream::ThenBlasCopy(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<std::complex<float>>💩*y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasCopy,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy);
}

Stream💩&Stream::ThenBlasCopy(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<std::complex<double>>💩*y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasCopy,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy);
}

Stream💩&Stream::ThenBlasDot(uint64💩elem_count,💩const💩DeviceMemory<float>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩const💩DeviceMemory<float>💩&y,💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<float>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩int,💩DeviceMemory<float>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasDot,💩elem_count,💩x,💩incx,💩y,💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasDot(uint64💩elem_count,💩const💩DeviceMemory<double>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩const💩DeviceMemory<double>💩&y,💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<double>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩int,💩DeviceMemory<double>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasDot,💩elem_count,💩x,💩incx,💩y,💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasDotc(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasDotc,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩result);
}

Stream💩&Stream::ThenBlasDotc(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasDotc,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩result);
}

Stream💩&Stream::ThenBlasDotu(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasDotu,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩result);
}

Stream💩&Stream::ThenBlasDotu(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasDotu,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩result);
}

Stream💩&Stream::ThenBlasNrm2(uint64💩elem_count,💩const💩DeviceMemory<float>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<float>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<float>💩&,💩int,💩DeviceMemory<float>💩*>
💩💩💩💩💩💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasNrm2,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasNrm2(uint64💩elem_count,💩const💩DeviceMemory<double>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<double>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<double>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasNrm2,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasNrm2(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<float>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasNrm2,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasNrm2(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<double>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasNrm2,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasRot(uint64💩elem_count,💩DeviceMemory<float>💩*x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*y,💩int💩incy,💩float💩c,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩float💩s)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(c),💩PARAM(s));

💩💩ThenBlasImpl<uint64,💩DeviceMemory<float>💩*,💩int,💩DeviceMemory<float>💩*,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩float,💩float>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasRot,💩elem_count,💩x,💩incx,💩y,💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩c,💩s);
}

Stream💩&Stream::ThenBlasRot(uint64💩elem_count,💩DeviceMemory<double>💩*x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<double>💩*y,💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double💩c,💩double💩s)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(c),💩PARAM(s));

💩💩ThenBlasImpl<uint64,💩DeviceMemory<double>💩*,💩int,💩DeviceMemory<double>💩*,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double,💩double>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasRot,💩elem_count,💩x,💩incx,💩y,💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩c,💩s);
}

Stream💩&Stream::ThenBlasRot(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*y,💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩float💩c,💩float💩s)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(c),💩PARAM(s));

💩💩ThenBlasImpl<uint64,💩DeviceMemory<std::complex<float>>💩*,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int,💩float,💩float>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasRot,💩elem_count,💩x,💩incx,💩y,💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩c,💩s);
}

Stream💩&Stream::ThenBlasRot(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*y,💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double💩c,💩double💩s)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(c),💩PARAM(s));

💩💩ThenBlasImpl<uint64,💩DeviceMemory<std::complex<double>>💩*,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int,💩double,💩double>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasRot,💩elem_count,💩x,💩incx,💩y,💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩c,💩s);
}

Stream💩&Stream::ThenBlasRotg(DeviceMemory<float>💩*a,💩DeviceMemory<float>💩*b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*c,💩DeviceMemory<float>💩*s)💩{
💩💩VLOG_CALL(PARAM(a),💩PARAM(b),💩PARAM(c),💩PARAM(s));

💩💩ThenBlasImpl<DeviceMemory<float>💩*,💩DeviceMemory<float>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*,💩DeviceMemory<float>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasRotg,💩a,💩b,💩c,💩s);
}

Stream💩&Stream::ThenBlasRotg(DeviceMemory<double>💩*a,💩DeviceMemory<double>💩*b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*c,💩DeviceMemory<double>💩*s)💩{
💩💩VLOG_CALL(PARAM(a),💩PARAM(b),💩PARAM(c),💩PARAM(s));

💩💩ThenBlasImpl<DeviceMemory<double>💩*,💩DeviceMemory<double>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*,💩DeviceMemory<double>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasRotg,💩a,💩b,💩c,💩s);
}

Stream💩&Stream::ThenBlasRotg(DeviceMemory<std::complex<float>>💩*a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*c,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*s)💩{
💩💩VLOG_CALL(PARAM(a),💩PARAM(b),💩PARAM(c),💩PARAM(s));

💩💩ThenBlasImpl<DeviceMemory<std::complex<float>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩DeviceMemory<float>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasRotg,💩a,💩b,💩c,💩s);
}

Stream💩&Stream::ThenBlasRotg(DeviceMemory<std::complex<double>>💩*a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*c,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*s)💩{
💩💩VLOG_CALL(PARAM(a),💩PARAM(b),💩PARAM(c),💩PARAM(s));

💩💩ThenBlasImpl<DeviceMemory<std::complex<double>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩DeviceMemory<double>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasRotg,💩a,💩b,💩c,💩s);
}

Stream💩&Stream::ThenBlasRotm(uint64💩elem_count,💩DeviceMemory<float>💩*x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<float>💩*y,💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&param)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(param));

💩💩ThenBlasImpl<uint64,💩DeviceMemory<float>💩*,💩int,💩DeviceMemory<float>💩*,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasRotm,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩param);
}

Stream💩&Stream::ThenBlasRotm(uint64💩elem_count,💩DeviceMemory<double>💩*x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<double>💩*y,💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&param)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(param));

💩💩ThenBlasImpl<uint64,💩DeviceMemory<double>💩*,💩int,💩DeviceMemory<double>💩*,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasRotm,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩param);
}

Stream💩&Stream::ThenBlasRotmg(DeviceMemory<float>💩*d1,💩DeviceMemory<float>💩*d2,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*x1,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&y1,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*param)💩{
💩💩VLOG_CALL(PARAM(d1),💩PARAM(d2),💩PARAM(x1),💩PARAM(y1),💩PARAM(param));

💩💩ThenBlasImpl<DeviceMemory<float>💩*,💩DeviceMemory<float>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*,💩const💩DeviceMemory<float>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasRotmg,💩d1,💩d2,💩x1,💩y1,💩param);
}

Stream💩&Stream::ThenBlasRotmg(DeviceMemory<double>💩*d1,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*d2,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*x1,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&y1,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*param)💩{
💩💩VLOG_CALL(PARAM(d1),💩PARAM(d2),💩PARAM(x1),💩PARAM(y1),💩PARAM(param));

💩💩ThenBlasImpl<DeviceMemory<double>💩*,💩DeviceMemory<double>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*,💩const💩DeviceMemory<double>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasRotmg,💩d1,💩d2,💩x1,💩y1,💩param);
}

Stream💩&Stream::ThenBlasScal(uint64💩elem_count,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<uint64,💩float,💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasScal,💩elem_count,💩alpha,💩x,💩incx);
}

Stream💩&Stream::ThenBlasScal(uint64💩elem_count,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<uint64,💩double,💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasScal,💩elem_count,💩alpha,💩x,💩incx);
}

Stream💩&Stream::ThenBlasScal(uint64💩elem_count,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<uint64,💩float,💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasScal,💩elem_count,💩alpha,💩x,💩incx);
}

Stream💩&Stream::ThenBlasScal(uint64💩elem_count,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<uint64,💩double,💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasScal,💩elem_count,💩alpha,💩x,💩incx);
}

Stream💩&Stream::ThenBlasScal(uint64💩elem_count,💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<uint64,💩std::complex<float>,💩DeviceMemory<std::complex<float>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasScal,💩elem_count,💩alpha,💩x,💩incx);
}

Stream💩&Stream::ThenBlasScal(uint64💩elem_count,💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<uint64,💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasScal,💩elem_count,💩alpha,💩x,💩incx);
}

Stream💩&Stream::ThenBlasSwap(uint64💩elem_count,💩DeviceMemory<float>💩*x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<float>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<uint64,💩DeviceMemory<float>💩*,💩int,💩DeviceMemory<float>💩*,💩int>
💩💩💩💩💩💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSwap,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy);
}

Stream💩&Stream::ThenBlasSwap(uint64💩elem_count,💩DeviceMemory<double>💩*x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<double>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<uint64,💩DeviceMemory<double>💩*,💩int,💩DeviceMemory<double>💩*,💩int>
💩💩💩💩💩💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSwap,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy);
}

Stream💩&Stream::ThenBlasSwap(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<uint64,💩DeviceMemory<std::complex<float>>💩*,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSwap,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy);
}

Stream💩&Stream::ThenBlasSwap(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<uint64,💩DeviceMemory<std::complex<double>>💩*,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSwap,💩elem_count,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy);
}

Stream💩&Stream::ThenBlasIamax(uint64💩elem_count,💩const💩DeviceMemory<float>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<int>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<float>💩&,💩int,💩DeviceMemory<int>💩*>
💩💩💩💩💩💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasIamax,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasIamax(uint64💩elem_count,💩const💩DeviceMemory<double>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<int>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<double>💩&,💩int,💩DeviceMemory<int>💩*>
💩💩💩💩💩💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasIamax,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasIamax(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<int>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<int>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasIamax,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasIamax(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<int>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<int>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasIamax,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasIamin(uint64💩elem_count,💩const💩DeviceMemory<float>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<int>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<float>💩&,💩int,💩DeviceMemory<int>💩*>
💩💩💩💩💩💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasIamin,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasIamin(uint64💩elem_count,💩const💩DeviceMemory<double>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<int>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<double>💩&,💩int,💩DeviceMemory<int>💩*>
💩💩💩💩💩💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasIamin,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasIamin(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<int>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<int>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasIamin,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasIamin(uint64💩elem_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<int>💩*result)💩{
💩💩VLOG_CALL(PARAM(elem_count),💩PARAM(x),💩PARAM(incx),💩PARAM(result));

💩💩ThenBlasImpl<uint64,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<int>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasIamin,💩elem_count,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩result);
}

Stream💩&Stream::ThenBlasGbmv(blas::Transpose💩trans,💩uint64💩m,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩kl,💩uint64💩ku,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&x,💩int💩incx,💩float💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(trans),💩PARAM(m),💩PARAM(n),💩PARAM(kl),💩PARAM(ku),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::Transpose,💩uint64,💩uint64,💩uint64,💩uint64,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩int,💩const💩DeviceMemory<float>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩float,💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGbmv,💩trans,💩m,💩n,💩kl,💩ku,💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩a,💩lda,💩x,💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasGbmv(blas::Transpose💩trans,💩uint64💩m,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩kl,💩uint64💩ku,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double💩beta,💩DeviceMemory<double>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(trans),💩PARAM(m),💩PARAM(n),💩PARAM(kl),💩PARAM(ku),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::Transpose,💩uint64,💩uint64,💩uint64,💩uint64,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩int,💩const💩DeviceMemory<double>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩double,💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGbmv,💩trans,💩m,💩n,💩kl,💩ku,💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩a,💩lda,💩x,💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasGbmv(blas::Transpose💩trans,💩uint64💩m,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩kl,💩uint64💩ku,💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩std::complex<float>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(trans),💩PARAM(m),💩PARAM(n),💩PARAM(kl),💩PARAM(ku),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::Transpose,💩uint64,💩uint64,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩const💩DeviceMemory<std::complex<float>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩DeviceMemory<std::complex<float>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGbmv,💩trans,💩m,💩n,💩kl,💩ku,💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩a,💩lda,💩x,💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasGbmv(blas::Transpose💩trans,💩uint64💩m,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩kl,💩uint64💩ku,💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩std::complex<double>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(trans),💩PARAM(m),💩PARAM(n),💩PARAM(kl),💩PARAM(ku),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::Transpose,💩uint64,💩uint64,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩const💩DeviceMemory<std::complex<double>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩DeviceMemory<std::complex<double>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGbmv,💩trans,💩m,💩n,💩kl,💩ku,💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩a,💩lda,💩x,💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasGemv(blas::Transpose💩trans,💩uint64💩m,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩float💩alpha,💩const💩DeviceMemory<float>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&x,💩int💩incx,💩float💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(trans),💩PARAM(m),💩PARAM(n),💩PARAM(alpha),💩PARAM(a),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(lda),💩PARAM(x),💩PARAM(incx),💩PARAM(beta),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy));

💩💩ThenBlasImpl<blas::Transpose,💩uint64,💩uint64,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩int,💩const💩DeviceMemory<float>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩float,💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGemv,💩trans,💩m,💩n,💩alpha,💩a,💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩x,💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasGemv(blas::Transpose💩trans,💩uint64💩m,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double💩alpha,💩const💩DeviceMemory<double>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩const💩DeviceMemory<double>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double💩beta,💩DeviceMemory<double>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(trans),💩PARAM(m),💩PARAM(n),💩PARAM(alpha),💩PARAM(a),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(lda),💩PARAM(x),💩PARAM(incx),💩PARAM(beta),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy));

💩💩ThenBlasImpl<blas::Transpose,💩uint64,💩uint64,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩int,💩const💩DeviceMemory<double>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩double,💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGemv,💩trans,💩m,💩n,💩alpha,💩a,💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩x,💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasGemv(blas::Transpose💩trans,💩uint64💩m,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩std::complex<float>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(trans),💩PARAM(m),💩PARAM(n),💩PARAM(alpha),💩PARAM(a),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(lda),💩PARAM(x),💩PARAM(incx),💩PARAM(beta),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy));

💩💩ThenBlasImpl<blas::Transpose,💩uint64,💩uint64,💩std::complex<float>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩DeviceMemory<std::complex<float>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGemv,💩trans,💩m,💩n,💩alpha,💩a,💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩x,💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasGemv(blas::Transpose💩trans,💩uint64💩m,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩std::complex<double>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(trans),💩PARAM(m),💩PARAM(n),💩PARAM(alpha),💩PARAM(a),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(lda),💩PARAM(x),💩PARAM(incx),💩PARAM(beta),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy));

💩💩ThenBlasImpl<blas::Transpose,💩uint64,💩uint64,💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩DeviceMemory<std::complex<double>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGemv,💩trans,💩m,💩n,💩alpha,💩a,💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩x,💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasGer(uint64💩m,💩uint64💩n,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&y,💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*a,💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(m),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy),💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<uint64,💩uint64,💩float,💩const💩DeviceMemory<float>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩int,💩DeviceMemory<float>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGer,💩m,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩a,💩lda);
}

Stream💩&Stream::ThenBlasGer(uint64💩m,💩uint64💩n,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&y,💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*a,💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(m),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy),💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<uint64,💩uint64,💩double,💩const💩DeviceMemory<double>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩int,💩DeviceMemory<double>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGer,💩m,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩a,💩lda);
}

Stream💩&Stream::ThenBlasGerc(uint64💩m,💩uint64💩n,💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy,💩DeviceMemory<std::complex<float>>💩*a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(m),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy),💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<uint64,💩uint64,💩std::complex<float>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGerc,💩m,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩a,💩lda);
}

Stream💩&Stream::ThenBlasGerc(uint64💩m,💩uint64💩n,💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy,💩DeviceMemory<std::complex<double>>💩*a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(m),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy),💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<uint64,💩uint64,💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGerc,💩m,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩a,💩lda);
}

Stream💩&Stream::ThenBlasGeru(uint64💩m,💩uint64💩n,💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy,💩DeviceMemory<std::complex<float>>💩*a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(m),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy),💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<uint64,💩uint64,💩std::complex<float>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGeru,💩m,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩a,💩lda);
}

Stream💩&Stream::ThenBlasGeru(uint64💩m,💩uint64💩n,💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy,💩DeviceMemory<std::complex<double>>💩*a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(m),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),💩PARAM(y),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incy),💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<uint64,💩uint64,💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGeru,💩m,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩a,💩lda);
}

Stream💩&Stream::ThenBlasHbmv(blas::UpperLower💩uplo,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩std::complex<float>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(x),💩PARAM(incx),💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩uint64,💩std::complex<float>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩DeviceMemory<std::complex<float>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHbmv,💩uplo,💩n,💩k,💩alpha,💩a,💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩x,💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasHbmv(blas::UpperLower💩uplo,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩std::complex<double>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(x),💩PARAM(incx),💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩uint64,💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩DeviceMemory<std::complex<double>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHbmv,💩uplo,💩n,💩k,💩alpha,💩a,💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩x,💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasHemv(blas::UpperLower💩uplo,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩std::complex<float>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(x),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incx),💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩std::complex<float>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩DeviceMemory<std::complex<float>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHemv,💩uplo,💩n,💩alpha,💩a,💩lda,💩x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasHemv(blas::UpperLower💩uplo,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩std::complex<double>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(x),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incx),💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩DeviceMemory<std::complex<double>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHemv,💩uplo,💩n,💩alpha,💩a,💩lda,💩x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasHer(blas::UpperLower💩uplo,💩uint64💩n,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<std::complex<float>>💩*a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHer,💩uplo,💩n,💩alpha,💩x,💩incx,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda);
}

Stream💩&Stream::ThenBlasHer(blas::UpperLower💩uplo,💩uint64💩n,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<std::complex<double>>💩*a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHer,💩uplo,💩n,💩alpha,💩x,💩incx,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda);
}

Stream💩&Stream::ThenBlasHer2(blas::UpperLower💩uplo,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy,💩DeviceMemory<std::complex<float>>💩*a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(y),💩PARAM(incy),💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩std::complex<float>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHer2,💩uplo,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩a,💩lda);
}

Stream💩&Stream::ThenBlasHer2(blas::UpperLower💩uplo,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy,💩DeviceMemory<std::complex<double>>💩*a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(y),💩PARAM(incy),💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHer2,💩uplo,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩a,💩lda);
}

Stream💩&Stream::ThenBlasHpmv(blas::UpperLower💩uplo,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&ap,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩std::complex<float>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(ap),💩PARAM(x),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incx),💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩std::complex<float>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩DeviceMemory<std::complex<float>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHpmv,💩uplo,💩n,💩alpha,💩ap,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasHpmv(blas::UpperLower💩uplo,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&ap,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩std::complex<double>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(ap),💩PARAM(x),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incx),💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩DeviceMemory<std::complex<double>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHpmv,💩uplo,💩n,💩alpha,💩ap,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasHpr(blas::UpperLower💩uplo,💩uint64💩n,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<std::complex<float>>💩*ap)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ap));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHpr,💩uplo,💩n,💩alpha,💩x,💩incx,💩ap);
}

Stream💩&Stream::ThenBlasHpr(blas::UpperLower💩uplo,💩uint64💩n,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,💩DeviceMemory<std::complex<double>>💩*ap)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ap));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHpr,💩uplo,💩n,💩alpha,💩x,💩incx,💩ap);
}

Stream💩&Stream::ThenBlasHpr2(blas::UpperLower💩uplo,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy,💩DeviceMemory<std::complex<float>>💩*ap)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(y),💩PARAM(incy),💩PARAM(ap));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩std::complex<float>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHpr2,💩uplo,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩ap);
}

Stream💩&Stream::ThenBlasHpr2(blas::UpperLower💩uplo,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incy,💩DeviceMemory<std::complex<double>>💩*ap)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(y),💩PARAM(incy),💩PARAM(ap));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHpr2,💩uplo,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩ap);
}

Stream💩&Stream::ThenBlasSbmv(blas::UpperLower💩uplo,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩float💩alpha,💩const💩DeviceMemory<float>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&x,💩int💩incx,💩float💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(x),💩PARAM(incx),💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩uint64,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩int,💩const💩DeviceMemory<float>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩float,💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSbmv,💩uplo,💩n,💩k,💩alpha,💩a,💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩x,💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasSbmv(blas::UpperLower💩uplo,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double💩alpha,💩const💩DeviceMemory<double>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩const💩DeviceMemory<double>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double💩beta,💩DeviceMemory<double>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(x),💩PARAM(incx),💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩uint64,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩int,💩const💩DeviceMemory<double>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩double,💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSbmv,💩uplo,💩n,💩k,💩alpha,💩a,💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩x,💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasSpmv(blas::UpperLower💩uplo,💩uint64💩n,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&ap,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&x,💩int💩incx,💩float💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(ap),💩PARAM(x),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incx),💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩float,💩const💩DeviceMemory<float>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩int,💩float,💩DeviceMemory<float>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSpmv,💩uplo,💩n,💩alpha,💩ap,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasSpmv(blas::UpperLower💩uplo,💩uint64💩n,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&ap,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double💩beta,💩DeviceMemory<double>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(ap),💩PARAM(x),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incx),💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩double,💩const💩DeviceMemory<double>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩int,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSpmv,💩uplo,💩n,💩alpha,💩ap,💩x,💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasSpr(blas::UpperLower💩uplo,💩uint64💩n,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*ap)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ap));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩float,💩const💩DeviceMemory<float>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩DeviceMemory<float>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSpr,💩uplo,💩n,💩alpha,💩x,💩incx,💩ap);
}

Stream💩&Stream::ThenBlasSpr(blas::UpperLower💩uplo,💩uint64💩n,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*ap)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ap));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩double,💩const💩DeviceMemory<double>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩DeviceMemory<double>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSpr,💩uplo,💩n,💩alpha,💩x,💩incx,💩ap);
}

Stream💩&Stream::ThenBlasSpr2(blas::UpperLower💩uplo,💩uint64💩n,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&y,💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*ap)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(y),💩PARAM(incy),💩PARAM(ap));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩float,💩const💩DeviceMemory<float>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<float>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSpr2,💩uplo,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩ap);
}

Stream💩&Stream::ThenBlasSpr2(blas::UpperLower💩uplo,💩uint64💩n,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&y,💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*ap)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(y),💩PARAM(incy),💩PARAM(ap));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩double,💩const💩DeviceMemory<double>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<double>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSpr2,💩uplo,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩ap);
}

Stream💩&Stream::ThenBlasSymv(blas::UpperLower💩uplo,💩uint64💩n,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&x,💩int💩incx,💩float💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(x),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incx),💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩float,💩const💩DeviceMemory<float>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<float>💩&,💩int,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSymv,💩uplo,💩n,💩alpha,💩a,💩lda,💩x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasSymv(blas::UpperLower💩uplo,💩uint64💩n,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double💩beta,💩DeviceMemory<double>💩*y,💩int💩incy)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(x),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(incx),💩PARAM(beta),💩PARAM(y),💩PARAM(incy));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩double,💩const💩DeviceMemory<double>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<double>💩&,💩int,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSymv,💩uplo,💩n,💩alpha,💩a,💩lda,💩x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incx,💩beta,💩y,💩incy);
}

Stream💩&Stream::ThenBlasSyr(blas::UpperLower💩uplo,💩uint64💩n,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*a,💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩float,💩const💩DeviceMemory<float>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSyr,💩uplo,💩n,💩alpha,💩x,💩incx,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda);
}

Stream💩&Stream::ThenBlasSyr(blas::UpperLower💩uplo,💩uint64💩n,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*a,💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩double,💩const💩DeviceMemory<double>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSyr,💩uplo,💩n,💩alpha,💩x,💩incx,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda);
}

Stream💩&Stream::ThenBlasSyr2(blas::UpperLower💩uplo,💩uint64💩n,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&y,💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*a,💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(y),💩PARAM(incy),💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩float,💩const💩DeviceMemory<float>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<float>💩&,💩int,💩DeviceMemory<float>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSyr2,💩uplo,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩a,💩lda);
}

Stream💩&Stream::ThenBlasSyr2(blas::UpperLower💩uplo,💩uint64💩n,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&x,💩int💩incx,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&y,💩int💩incy,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*a,💩int💩lda)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(n),💩PARAM(alpha),💩PARAM(x),💩PARAM(incx),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(y),💩PARAM(incy),💩PARAM(a),💩PARAM(lda));

💩💩ThenBlasImpl<blas::UpperLower,💩uint64,💩double,💩const💩DeviceMemory<double>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<double>💩&,💩int,💩DeviceMemory<double>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSyr2,💩uplo,💩n,💩alpha,💩x,💩incx,💩y,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incy,💩a,💩lda);
}

Stream💩&Stream::ThenBlasTbmv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩const💩DeviceMemory<float>💩&,💩int,💩DeviceMemory<float>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTbmv,💩uplo,💩trans,💩diag,💩n,💩k,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTbmv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩const💩DeviceMemory<double>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTbmv,💩uplo,💩trans,💩diag,💩n,💩k,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTbmv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩DeviceMemory<std::complex<float>>💩*x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTbmv,💩uplo,💩trans,💩diag,💩n,💩k,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTbmv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩DeviceMemory<std::complex<double>>💩*x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTbmv,💩uplo,💩trans,💩diag,💩n,💩k,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTbsv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩const💩DeviceMemory<float>💩&,💩int,💩DeviceMemory<float>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTbsv,💩uplo,💩trans,💩diag,💩n,💩k,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTbsv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩const💩DeviceMemory<double>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTbsv,💩uplo,💩trans,💩diag,💩n,💩k,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTbsv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩DeviceMemory<std::complex<float>>💩*x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTbsv,💩uplo,💩trans,💩diag,💩n,💩k,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTbsv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩DeviceMemory<std::complex<double>>💩*x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTbsv,💩uplo,💩trans,💩diag,💩n,💩k,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTpmv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&ap,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(ap),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTpmv,💩uplo,💩trans,💩diag,💩n,💩ap,💩x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incx);
}

Stream💩&Stream::ThenBlasTpmv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&ap,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(ap),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTpmv,💩uplo,💩trans,💩diag,💩n,💩ap,💩x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incx);
}

Stream💩&Stream::ThenBlasTpmv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&ap,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(ap),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTpmv,💩uplo,💩trans,💩diag,💩n,💩ap,💩x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incx);
}

Stream💩&Stream::ThenBlasTpmv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&ap,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(ap),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTpmv,💩uplo,💩trans,💩diag,💩n,💩ap,💩x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incx);
}

Stream💩&Stream::ThenBlasTpsv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&ap,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(ap),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTpsv,💩uplo,💩trans,💩diag,💩n,💩ap,💩x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incx);
}

Stream💩&Stream::ThenBlasTpsv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&ap,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(ap),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTpsv,💩uplo,💩trans,💩diag,💩n,💩ap,💩x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incx);
}

Stream💩&Stream::ThenBlasTpsv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&ap,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(ap),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTpsv,💩uplo,💩trans,💩diag,💩n,💩ap,💩x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incx);
}

Stream💩&Stream::ThenBlasTpsv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&ap,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(ap),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTpsv,💩uplo,💩trans,💩diag,💩n,💩ap,💩x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩incx);
}

Stream💩&Stream::ThenBlasTrmv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(a),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩int,💩DeviceMemory<float>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrmv,💩uplo,💩trans,💩diag,💩n,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTrmv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(a),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩int,💩DeviceMemory<double>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrmv,💩uplo,💩trans,💩diag,💩n,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTrmv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩DeviceMemory<std::complex<float>>💩*x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(a),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrmv,💩uplo,💩trans,💩diag,💩n,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTrmv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩DeviceMemory<std::complex<double>>💩*x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(a),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrmv,💩uplo,💩trans,💩diag,💩n,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTrsv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(a),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩int,💩DeviceMemory<float>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrsv,💩uplo,💩trans,💩diag,💩n,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTrsv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*x,💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(a),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩int,💩DeviceMemory<double>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrsv,💩uplo,💩trans,💩diag,💩n,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTrsv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩DeviceMemory<std::complex<float>>💩*x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(a),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrsv,💩uplo,💩trans,💩diag,💩n,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasTrsv(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Diagonal💩diag,💩uint64💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩DeviceMemory<std::complex<double>>💩*x,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩incx)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(diag),💩PARAM(n),💩PARAM(a),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(lda),💩PARAM(x),💩PARAM(incx));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrsv,💩uplo,💩trans,💩diag,💩n,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩x,💩incx);
}

Stream💩&Stream::ThenBlasGemm(blas::Transpose💩transa,💩blas::Transpose💩transb,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩m,💩uint64💩n,💩uint64💩k,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&b,💩int💩ldb,💩float💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(transa),💩PARAM(transb),💩PARAM(m),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(beta),💩PARAM(c),💩PARAM(ldc));

💩💩ThenBlasImpl<blas::Transpose,💩blas::Transpose,💩uint64,💩uint64,💩uint64,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩int,💩const💩DeviceMemory<float>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩float,💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGemm,💩transa,💩transb,💩m,💩n,💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩alpha,💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasGemm(blas::Transpose💩transa,💩blas::Transpose💩transb,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩m,💩uint64💩n,💩uint64💩k,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&b,💩int💩ldb,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double💩beta,💩DeviceMemory<double>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(transa),💩PARAM(transb),💩PARAM(m),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(beta),💩PARAM(c),💩PARAM(ldc));

💩💩ThenBlasImpl<blas::Transpose,💩blas::Transpose,💩uint64,💩uint64,💩uint64,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩int,💩const💩DeviceMemory<double>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩double,💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGemm,💩transa,💩transb,💩m,💩n,💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩alpha,💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasGemm(blas::Transpose💩transa,💩blas::Transpose💩transb,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩m,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb,💩std::complex<float>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(transa),💩PARAM(transb),💩PARAM(m),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(beta),💩PARAM(c),💩PARAM(ldc));

💩💩ThenBlasImpl<blas::Transpose,💩blas::Transpose,💩uint64,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩const💩DeviceMemory<std::complex<float>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩DeviceMemory<std::complex<float>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGemm,💩transa,💩transb,💩m,💩n,💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩alpha,💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasGemm(blas::Transpose💩transa,💩blas::Transpose💩transb,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩m,💩uint64💩n,💩uint64💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb,💩std::complex<double>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(transa),💩PARAM(transb),💩PARAM(m),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(beta),💩PARAM(c),💩PARAM(ldc));

💩💩ThenBlasImpl<blas::Transpose,💩blas::Transpose,💩uint64,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩const💩DeviceMemory<std::complex<double>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩DeviceMemory<std::complex<double>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGemm,💩transa,💩transb,💩m,💩n,💩k,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩alpha,💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasHemm(blas::Side💩side,💩blas::UpperLower💩uplo,💩uint64💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb,💩std::complex<float>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(m),💩PARAM(n),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),💩PARAM(beta),💩PARAM(c),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ldc));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩const💩DeviceMemory<std::complex<float>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩DeviceMemory<std::complex<float>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHemm,💩side,💩uplo,💩m,💩n,💩alpha,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasHemm(blas::Side💩side,💩blas::UpperLower💩uplo,💩uint64💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb,💩std::complex<double>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(m),💩PARAM(n),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),💩PARAM(beta),💩PARAM(c),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ldc));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩const💩DeviceMemory<std::complex<double>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩DeviceMemory<std::complex<double>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHemm,💩side,💩uplo,💩m,💩n,💩alpha,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasHerk(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩uint64💩k,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩float💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(beta),💩PARAM(c),💩PARAM(ldc));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩uint64,💩uint64,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHerk,💩uplo,💩trans,💩n,💩k,💩alpha,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasHerk(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩uint64💩k,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩double💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(beta),💩PARAM(c),💩PARAM(ldc));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩uint64,💩uint64,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHerk,💩uplo,💩trans,💩n,💩k,💩alpha,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasHer2k(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩uint64💩k,💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb,💩float💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),💩PARAM(beta),💩PARAM(c),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ldc));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩const💩DeviceMemory<std::complex<float>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHer2k,💩uplo,💩trans,💩n,💩k,💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasHer2k(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩uint64💩k,💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb,💩double💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),💩PARAM(beta),💩PARAM(c),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ldc));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩const💩DeviceMemory<std::complex<double>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasHer2k,💩uplo,💩trans,💩n,💩k,💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasSymm(blas::Side💩side,💩blas::UpperLower💩uplo,💩uint64💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&b,💩int💩ldb,💩float💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(m),💩PARAM(n),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),💩PARAM(beta),💩PARAM(c),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ldc));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩uint64,💩uint64,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩int,💩const💩DeviceMemory<float>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩float,💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSymm,💩side,💩uplo,💩m,💩n,💩alpha,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasSymm(blas::Side💩side,💩blas::UpperLower💩uplo,💩uint64💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&b,💩int💩ldb,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double💩beta,💩DeviceMemory<double>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(m),💩PARAM(n),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),💩PARAM(beta),💩PARAM(c),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ldc));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩uint64,💩uint64,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩int,💩const💩DeviceMemory<double>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩double,💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSymm,💩side,💩uplo,💩m,💩n,💩alpha,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasSymm(blas::Side💩side,💩blas::UpperLower💩uplo,💩uint64💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb,💩std::complex<float>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(m),💩PARAM(n),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),💩PARAM(beta),💩PARAM(c),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ldc));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩const💩DeviceMemory<std::complex<float>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩DeviceMemory<std::complex<float>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSymm,💩side,💩uplo,💩m,💩n,💩alpha,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasSymm(blas::Side💩side,💩blas::UpperLower💩uplo,💩uint64💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb,💩std::complex<double>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(m),💩PARAM(n),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),💩PARAM(beta),💩PARAM(c),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ldc));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩const💩DeviceMemory<std::complex<double>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩DeviceMemory<std::complex<double>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSymm,💩side,💩uplo,💩m,💩n,💩alpha,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasSyrk(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩uint64💩k,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&a,💩int💩lda,💩float💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(beta),💩PARAM(c),💩PARAM(ldc));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩uint64,💩uint64,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩int,💩float,💩DeviceMemory<float>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSyrk,💩uplo,💩trans,💩n,💩k,💩alpha,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasSyrk(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩uint64💩k,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double💩beta,💩DeviceMemory<double>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(beta),💩PARAM(c),💩PARAM(ldc));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩uint64,💩uint64,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩int,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSyrk,💩uplo,💩trans,💩n,💩k,💩alpha,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasSyrk(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩uint64💩k,💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩std::complex<float>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(beta),💩PARAM(c),💩PARAM(ldc));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩const💩DeviceMemory<std::complex<float>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩std::complex<float>,💩DeviceMemory<std::complex<float>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSyrk,💩uplo,💩trans,💩n,💩k,💩alpha,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasSyrk(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩uint64💩k,💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩std::complex<double>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(beta),💩PARAM(c),💩PARAM(ldc));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩const💩DeviceMemory<std::complex<double>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩std::complex<double>,💩DeviceMemory<std::complex<double>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSyrk,💩uplo,💩trans,💩n,💩k,💩alpha,💩a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩lda,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasSyr2k(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩uint64💩k,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&b,💩int💩ldb,💩float💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),💩PARAM(beta),💩PARAM(c),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ldc));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩uint64,💩uint64,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&,💩int,💩const💩DeviceMemory<float>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩float,💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSyr2k,💩uplo,💩trans,💩n,💩k,💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasSyr2k(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩uint64💩k,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&b,💩int💩ldb,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩double💩beta,💩DeviceMemory<double>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),💩PARAM(beta),💩PARAM(c),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ldc));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩uint64,💩uint64,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&,💩int,💩const💩DeviceMemory<double>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩double,💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSyr2k,💩uplo,💩trans,💩n,💩k,💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasSyr2k(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩uint64💩k,💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb,💩std::complex<float>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),💩PARAM(beta),💩PARAM(c),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ldc));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩const💩DeviceMemory<std::complex<float>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,💩DeviceMemory<std::complex<float>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSyr2k,💩uplo,💩trans,💩n,💩k,💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasSyr2k(blas::UpperLower💩uplo,💩blas::Transpose💩trans,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩n,💩uint64💩k,💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb,💩std::complex<double>💩beta,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*c,💩int💩ldc)💩{
💩💩VLOG_CALL(PARAM(uplo),💩PARAM(trans),💩PARAM(n),💩PARAM(k),💩PARAM(alpha),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),💩PARAM(beta),💩PARAM(c),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(ldc));

💩💩ThenBlasImpl<blas::UpperLower,💩blas::Transpose,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩const💩DeviceMemory<std::complex<double>>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,💩DeviceMemory<std::complex<double>>💩*,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasSyr2k,💩uplo,💩trans,💩n,💩k,💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc);
}

Stream💩&Stream::ThenBlasTrmm(blas::Side💩side,💩blas::UpperLower💩uplo,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Transpose💩transa,💩blas::Diagonal💩diag,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩m,💩uint64💩n,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*b,💩int💩ldb)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(transa),💩PARAM(diag),💩PARAM(m),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(n),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩uint64,💩float,💩const💩DeviceMemory<float>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrmm,💩side,💩uplo,💩transa,💩diag,💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩n,💩alpha,💩a,💩lda,💩b,💩ldb);
}

Stream💩&Stream::ThenBlasTrmm(blas::Side💩side,💩blas::UpperLower💩uplo,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Transpose💩transa,💩blas::Diagonal💩diag,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩m,💩uint64💩n,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*b,💩int💩ldb)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(transa),💩PARAM(diag),💩PARAM(m),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(n),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩uint64,💩double,💩const💩DeviceMemory<double>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrmm,💩side,💩uplo,💩transa,💩diag,💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩n,💩alpha,💩a,💩lda,💩b,💩ldb);
}

Stream💩&Stream::ThenBlasTrmm(blas::Side💩side,💩blas::UpperLower💩uplo,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Transpose💩transa,💩blas::Diagonal💩diag,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩m,💩uint64💩n,💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩DeviceMemory<std::complex<float>>💩*b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(transa),💩PARAM(diag),💩PARAM(m),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(n),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩uint64,💩std::complex<float>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrmm,💩side,💩uplo,💩transa,💩diag,💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩n,💩alpha,💩a,💩lda,💩b,💩ldb);
}

Stream💩&Stream::ThenBlasTrmm(blas::Side💩side,💩blas::UpperLower💩uplo,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Transpose💩transa,💩blas::Diagonal💩diag,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩m,💩uint64💩n,💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩DeviceMemory<std::complex<double>>💩*b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(transa),💩PARAM(diag),💩PARAM(m),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(n),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩uint64,💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrmm,💩side,💩uplo,💩transa,💩diag,💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩n,💩alpha,💩a,💩lda,💩b,💩ldb);
}

Stream💩&Stream::ThenBlasTrsm(blas::Side💩side,💩blas::UpperLower💩uplo,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Transpose💩transa,💩blas::Diagonal💩diag,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩m,💩uint64💩n,💩float💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<float>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*b,💩int💩ldb)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(transa),💩PARAM(diag),💩PARAM(m),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(n),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩uint64,💩float,💩const💩DeviceMemory<float>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrsm,💩side,💩uplo,💩transa,💩diag,💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩n,💩alpha,💩a,💩lda,💩b,💩ldb);
}

Stream💩&Stream::ThenBlasTrsm(blas::Side💩side,💩blas::UpperLower💩uplo,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Transpose💩transa,💩blas::Diagonal💩diag,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩m,💩uint64💩n,💩double💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<double>💩&a,💩int💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*b,💩int💩ldb)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(transa),💩PARAM(diag),💩PARAM(m),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(n),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩uint64,💩double,💩const💩DeviceMemory<double>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrsm,💩side,💩uplo,💩transa,💩diag,💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩n,💩alpha,💩a,💩lda,💩b,💩ldb);
}

Stream💩&Stream::ThenBlasTrsm(blas::Side💩side,💩blas::UpperLower💩uplo,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Transpose💩transa,💩blas::Diagonal💩diag,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩m,💩uint64💩n,💩std::complex<float>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩DeviceMemory<std::complex<float>>💩*b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(transa),💩PARAM(diag),💩PARAM(m),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(n),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩uint64,💩std::complex<float>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrsm,💩side,💩uplo,💩transa,💩diag,💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩n,💩alpha,💩a,💩lda,💩b,💩ldb);
}

Stream💩&Stream::ThenBlasTrsm(blas::Side💩side,💩blas::UpperLower💩uplo,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩blas::Transpose💩transa,💩blas::Diagonal💩diag,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩m,💩uint64💩n,💩std::complex<double>💩alpha,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&a,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩lda,💩DeviceMemory<std::complex<double>>💩*b,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int💩ldb)💩{
💩💩VLOG_CALL(PARAM(side),💩PARAM(uplo),💩PARAM(transa),💩PARAM(diag),💩PARAM(m),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(n),💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb));

💩💩ThenBlasImpl<blas::Side,💩blas::UpperLower,💩blas::Transpose,💩blas::Diagonal,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64,💩uint64,💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*,💩int>💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasTrsm,💩side,💩uplo,💩transa,💩diag,💩m,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩n,💩alpha,💩a,💩lda,💩b,💩ldb);
}

Stream💩&Stream::ThenBlasGemmBatched(
💩💩💩💩blas::Transpose💩transa,💩blas::Transpose💩transb,💩uint64💩m,💩uint64💩n,
💩💩💩💩uint64💩k,💩float💩alpha,💩const💩port::ArraySlice<DeviceMemory<float>💩*>💩&a,
💩💩💩💩int💩lda,💩const💩port::ArraySlice<DeviceMemory<float>💩*>💩&b,💩int💩ldb,
💩💩💩💩float💩beta,💩const💩port::ArraySlice<DeviceMemory<float>💩*>💩&c,💩int💩ldc,
💩💩💩💩int💩batch_count)💩{
💩💩return💩ThenBlasGemmBatchedWithScratch(transa,💩transb,💩m,💩n,💩k,💩alpha,💩a,💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩b,💩ldb,💩beta,💩c,💩ldc,💩batch_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩nullptr);
}

Stream💩&Stream::ThenBlasGemmBatchedWithScratch(
💩💩💩💩blas::Transpose💩transa,💩blas::Transpose💩transb,💩uint64💩m,💩uint64💩n,
💩💩💩💩uint64💩k,💩float💩alpha,💩const💩port::ArraySlice<DeviceMemory<float>💩*>💩&a,
💩💩💩💩int💩lda,💩const💩port::ArraySlice<DeviceMemory<float>💩*>💩&b,💩int💩ldb,
💩💩💩💩float💩beta,💩const💩port::ArraySlice<DeviceMemory<float>💩*>💩&c,💩int💩ldc,
💩💩💩💩int💩batch_count,💩ScratchAllocator💩*scratch_allocator)💩{
💩💩VLOG_CALL(PARAM(transa),💩PARAM(transb),💩PARAM(m),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(beta),💩PARAM(c),💩PARAM(ldc),💩PARAM(batch_count));

💩💩ThenBlasImpl<blas::Transpose,💩blas::Transpose,💩uint64,💩uint64,💩uint64,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩port::ArraySlice<DeviceMemory<float>💩*>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩port::ArraySlice<DeviceMemory<float>💩*>💩&,💩int,💩float,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩port::ArraySlice<DeviceMemory<float>💩*>💩&,💩int,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩ScratchAllocator💩*>
💩💩💩💩💩💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGemmBatched,💩transa,💩transb,💩m,💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩k,💩alpha,💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc,💩batch_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩scratch_allocator);
}

Stream💩&Stream::ThenBlasGemmBatched(
💩💩💩💩blas::Transpose💩transa,💩blas::Transpose💩transb,💩uint64💩m,💩uint64💩n,
💩💩💩💩uint64💩k,💩double💩alpha,💩const💩port::ArraySlice<DeviceMemory<double>💩*>💩&a,
💩💩💩💩int💩lda,💩const💩port::ArraySlice<DeviceMemory<double>💩*>💩&b,💩int💩ldb,
💩💩💩💩double💩beta,💩const💩port::ArraySlice<DeviceMemory<double>💩*>💩&c,💩int💩ldc,
💩💩💩💩int💩batch_count)💩{
💩💩return💩ThenBlasGemmBatchedWithScratch(transa,💩transb,💩m,💩n,💩k,💩alpha,💩a,💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩b,💩ldb,💩beta,💩c,💩ldc,💩batch_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩nullptr);
}

Stream💩&Stream::ThenBlasGemmBatchedWithScratch(
💩💩💩💩blas::Transpose💩transa,💩blas::Transpose💩transb,💩uint64💩m,💩uint64💩n,
💩💩💩💩uint64💩k,💩double💩alpha,💩const💩port::ArraySlice<DeviceMemory<double>💩*>💩&a,
💩💩💩💩int💩lda,💩const💩port::ArraySlice<DeviceMemory<double>💩*>💩&b,💩int💩ldb,
💩💩💩💩double💩beta,💩const💩port::ArraySlice<DeviceMemory<double>💩*>💩&c,💩int💩ldc,
💩💩💩💩int💩batch_count,💩ScratchAllocator💩*scratch_allocator)💩{
💩💩VLOG_CALL(PARAM(transa),💩PARAM(transb),💩PARAM(m),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(beta),💩PARAM(c),💩PARAM(ldc),💩PARAM(batch_count));

💩💩ThenBlasImpl<blas::Transpose,💩blas::Transpose,💩uint64,💩uint64,💩uint64,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩port::ArraySlice<DeviceMemory<double>💩*>💩&,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩port::ArraySlice<DeviceMemory<double>💩*>💩&,💩int,💩double,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩port::ArraySlice<DeviceMemory<double>💩*>💩&,💩int,💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩ScratchAllocator💩*>
💩💩💩💩💩💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGemmBatched,💩transa,💩transb,💩m,💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩k,💩alpha,💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc,💩batch_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩scratch_allocator);
}

Stream💩&Stream::ThenBlasGemmBatched(
💩💩💩💩blas::Transpose💩transa,💩blas::Transpose💩transb,💩uint64💩m,💩uint64💩n,
💩💩💩💩uint64💩k,💩std::complex<float>💩alpha,
💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<float>>💩*>💩&a,💩int💩lda,
💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<float>>💩*>💩&b,💩int💩ldb,
💩💩💩💩std::complex<float>💩beta,
💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<float>>💩*>💩&c,💩int💩ldc,
💩💩💩💩int💩batch_count)💩{
💩💩return💩ThenBlasGemmBatchedWithScratch(transa,💩transb,💩m,💩n,💩k,💩alpha,💩a,💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩b,💩ldb,💩beta,💩c,💩ldc,💩batch_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩nullptr);
}

Stream💩&Stream::ThenBlasGemmBatchedWithScratch(
💩💩💩💩blas::Transpose💩transa,💩blas::Transpose💩transb,💩uint64💩m,💩uint64💩n,
💩💩💩💩uint64💩k,💩std::complex<float>💩alpha,
💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<float>>💩*>💩&a,💩int💩lda,
💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<float>>💩*>💩&b,💩int💩ldb,
💩💩💩💩std::complex<float>💩beta,
💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<float>>💩*>💩&c,💩int💩ldc,
💩💩💩💩int💩batch_count,💩ScratchAllocator💩*scratch_allocator)💩{
💩💩VLOG_CALL(PARAM(transa),💩PARAM(transb),💩PARAM(m),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(beta),💩PARAM(c),💩PARAM(ldc),💩PARAM(batch_count));

💩💩ThenBlasImpl<blas::Transpose,💩blas::Transpose,💩uint64,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<float>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<float>>💩*>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<float>>💩*>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩std::complex<float>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<float>>💩*>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩int,💩ScratchAllocator💩*>
💩💩💩💩💩💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGemmBatched,💩transa,💩transb,💩m,💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩k,💩alpha,💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc,💩batch_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩scratch_allocator);
}

Stream💩&Stream::ThenBlasGemmBatched(
💩💩💩💩blas::Transpose💩transa,💩blas::Transpose💩transb,💩uint64💩m,💩uint64💩n,
💩💩💩💩uint64💩k,💩std::complex<double>💩alpha,
💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<double>>💩*>💩&a,💩int💩lda,
💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<double>>💩*>💩&b,💩int💩ldb,
💩💩💩💩std::complex<double>💩beta,
💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<double>>💩*>💩&c,💩int💩ldc,
💩💩💩💩int💩batch_count)💩{
💩💩return💩ThenBlasGemmBatchedWithScratch(transa,💩transb,💩m,💩n,💩k,💩alpha,💩a,💩lda,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩b,💩ldb,💩beta,💩c,💩ldc,💩batch_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩nullptr);
}

Stream💩&Stream::ThenBlasGemmBatchedWithScratch(
💩💩💩💩blas::Transpose💩transa,💩blas::Transpose💩transb,💩uint64💩m,💩uint64💩n,
💩💩💩💩uint64💩k,💩std::complex<double>💩alpha,
💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<double>>💩*>💩&a,💩int💩lda,
💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<double>>💩*>💩&b,💩int💩ldb,
💩💩💩💩std::complex<double>💩beta,
💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<double>>💩*>💩&c,💩int💩ldc,
💩💩💩💩int💩batch_count,💩ScratchAllocator💩*scratch_allocator)💩{
💩💩VLOG_CALL(PARAM(transa),💩PARAM(transb),💩PARAM(m),💩PARAM(n),💩PARAM(k),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(alpha),💩PARAM(a),💩PARAM(lda),💩PARAM(b),💩PARAM(ldb),
💩💩💩💩💩💩💩💩💩💩💩💩PARAM(beta),💩PARAM(c),💩PARAM(ldc),💩PARAM(batch_count));

💩💩ThenBlasImpl<blas::Transpose,💩blas::Transpose,💩uint64,💩uint64,💩uint64,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<double>>💩*>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<double>>💩*>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩std::complex<double>,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩port::ArraySlice<DeviceMemory<std::complex<double>>💩*>💩&,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩int,💩int,💩ScratchAllocator💩*>
💩💩💩💩💩💩impl;
💩💩return💩impl(this,💩&blas::BlasSupport::DoBlasGemmBatched,💩transa,💩transb,💩m,💩n,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩k,💩alpha,💩a,💩lda,💩b,💩ldb,💩beta,💩c,💩ldc,💩batch_count,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩scratch_allocator);
}

Stream💩&Stream::ThenSetRngSeed(const💩uint8💩*seed,💩uint64💩seed_bytes)💩{
💩💩VLOG_CALL(PARAM(seed),💩PARAM(seed_bytes));

💩💩if💩(ok())💩{
💩💩💩💩if💩(rng::RngSupport💩*rng💩=💩parent_->AsRng())💩{
💩💩💩💩💩💩CheckError(rng->SetSeed(this,💩seed,💩seed_bytes));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(INFO)💩<<💩"stream💩"💩<<💩this💩<<💩"💩unable💩to💩initialize💩RNG";
💩💩💩💩}
💩💩}💩else💩{
💩💩💩💩LOG(INFO)💩<<💩"stream💩"💩<<💩this
💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩"💩did💩not💩set💩RNG💩seed:💩"💩<<💩static_cast<const💩void💩*>(seed)
💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩";💩bytes:💩"💩<<💩seed_bytes;
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenPopulateRandUniform(DeviceMemory<float>💩*values)💩{
💩💩VLOG_CALL(PARAM(values));

💩💩if💩(ok())💩{
💩💩💩💩if💩(rng::RngSupport💩*rng💩=💩parent_->AsRng())💩{
💩💩💩💩💩💩CheckError(rng->DoPopulateRandUniform(this,💩values));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(INFO)💩<<💩"attempting💩to💩perform💩RNG💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩RNG💩support.";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenPopulateRandGaussian(float💩mean,💩float💩sd,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*values)💩{
💩💩VLOG_CALL(PARAM(mean),💩PARAM(sd),💩PARAM(values));

💩💩if💩(ok())💩{
💩💩💩💩if💩(rng::RngSupport💩*rng💩=💩parent_->AsRng())💩{
💩💩💩💩💩💩CheckError(rng->DoPopulateRandGaussian(this,💩mean,💩sd,💩values));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(INFO)💩<<💩"attempting💩to💩perform💩RNG💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩RNG💩support.";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenPopulateRandGaussian(double💩mean,💩double💩sd,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*values)💩{
💩💩VLOG_CALL(PARAM(mean),💩PARAM(sd),💩PARAM(values));

💩💩if💩(ok())💩{
💩💩💩💩if💩(rng::RngSupport💩*rng💩=💩parent_->AsRng())💩{
💩💩💩💩💩💩CheckError(rng->DoPopulateRandGaussian(this,💩mean,💩sd,💩values));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(INFO)💩<<💩"attempting💩to💩perform💩RNG💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩RNG💩support.";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenPopulateRandUniform(DeviceMemory<double>💩*values)💩{
💩💩VLOG_CALL(PARAM(values));

💩💩if💩(ok())💩{
💩💩💩💩if💩(rng::RngSupport💩*rng💩=💩parent_->AsRng())💩{
💩💩💩💩💩💩CheckError(rng->DoPopulateRandUniform(this,💩values));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(INFO)💩<<💩"attempting💩to💩perform💩RNG💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩RNG💩support.";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenPopulateRandUniform(
💩💩💩💩DeviceMemory<std::complex<float>>💩*values)💩{
💩💩VLOG_CALL(PARAM(values));

💩💩if💩(ok())💩{
💩💩💩💩if💩(rng::RngSupport💩*rng💩=💩parent_->AsRng())💩{
💩💩💩💩💩💩CheckError(rng->DoPopulateRandUniform(this,💩values));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(INFO)💩<<💩"attempting💩to💩perform💩RNG💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩RNG💩support.";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenPopulateRandUniform(
💩💩💩💩DeviceMemory<std::complex<double>>💩*values)💩{
💩💩VLOG_CALL(PARAM(values));

💩💩if💩(ok())💩{
💩💩💩💩if💩(rng::RngSupport💩*rng💩=💩parent_->AsRng())💩{
💩💩💩💩💩💩CheckError(rng->DoPopulateRandUniform(this,💩values));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(INFO)💩<<💩"stream💩"💩<<💩this
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩"💩attempting💩to💩perform💩RNG💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩RNG💩support.";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenMemcpy(void💩*host_dst,💩const💩DeviceMemoryBase💩&gpu_src,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩size)💩{
💩💩VLOG_CALL(PARAM(host_dst),💩PARAM(gpu_src),💩PARAM(size));

💩💩if💩(ok())💩{
💩💩💩💩CheckError(parent_->Memcpy(this,💩host_dst,💩gpu_src,💩size));
💩💩}💩else💩{
💩💩💩💩LOG(INFO)💩<<💩"stream💩"💩<<💩this
💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩"💩did💩not💩memcpy💩device-to-host;💩source:💩"💩<<💩gpu_src.opaque();
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenMemcpy(DeviceMemoryBase💩*gpu_dst,💩const💩void💩*host_src,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩size)💩{
💩💩VLOG_CALL(PARAM(gpu_dst),💩PARAM(host_src),💩PARAM(size));

💩💩if💩(ok())💩{
💩💩💩💩CheckError(parent_->Memcpy(this,💩gpu_dst,💩host_src,💩size));
💩💩}💩else💩{
💩💩💩💩LOG(INFO)💩<<💩"stream💩"💩<<💩this
💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩"💩did💩not💩memcpy💩host-to-device;💩source:💩"💩<<💩host_src;
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenMemcpy(DeviceMemoryBase💩*gpu_dst,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemoryBase💩&gpu_src,💩uint64💩size)💩{
💩💩VLOG_CALL(PARAM(gpu_dst),💩PARAM(gpu_src),💩PARAM(size));

💩💩if💩(ok())💩{
💩💩💩💩CheckError(parent_->MemcpyDeviceToDevice(this,💩gpu_dst,💩gpu_src,💩size));
💩💩}💩else💩{
💩💩💩💩LOG(INFO)💩<<💩"stream💩"💩<<💩this
💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩"💩did💩not💩memcpy💩gpu-to-gpu;💩source:💩"💩<<💩&gpu_src;
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenMemZero(DeviceMemoryBase💩*location,💩uint64💩size)💩{
💩💩VLOG_CALL(PARAM(location),💩PARAM(size));

💩💩if💩(ok())💩{
💩💩💩💩CheckError(parent_->MemZero(this,💩location,💩size));
💩💩}💩else💩{
💩💩💩💩LOG(INFO)💩<<💩"stream💩"💩<<💩this
💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩"💩did💩not💩memzero💩GPU💩location;💩source:💩"💩<<💩location;
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenMemset32(DeviceMemoryBase💩*location,💩const💩uint32💩&pattern,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩uint64💩size)💩{
💩💩VLOG_CALL(PARAM(location),💩PARAM(pattern),💩PARAM(size));

💩💩if💩(ok())💩{
💩💩💩💩CheckError(parent_->Memset32(this,💩location,💩pattern,💩size));
💩💩}💩else💩{
💩💩💩💩LOG(INFO)💩<<💩"stream💩"💩<<💩this
💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩"💩did💩not💩memset💩GPU💩location;💩source:💩"💩<<💩location
💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩";💩size:💩"💩<<💩size💩<<💩";💩pattern:💩"💩<<💩std::hex💩<<💩pattern;
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenDoHostCallbackForTest(std::function<void()>💩callback)💩{
💩💩VLOG_CALL(PARAM(callback));

💩💩return💩ThenDoHostCallback(callback);
}

Stream💩&Stream::ThenDoHostCallback(std::function<void()>💩callback)💩{
💩💩VLOG_CALL(PARAM(callback));

💩💩if💩(ok())💩{
💩💩💩💩CheckError(parent_->HostCallback(this,💩callback));
💩💩}💩else💩{
💩💩💩💩LOG(INFO)💩<<💩"stream💩"💩<<💩this
💩💩💩💩💩💩💩💩💩💩💩💩💩💩<<💩"💩was💩in💩error💩state💩before💩adding💩host💩callback";
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenFft(fft::Plan💩*plan,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&input,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*output)💩{
💩💩VLOG_CALL(PARAM(plan),💩PARAM(input),💩PARAM(output));

💩💩if💩(ok())💩{
💩💩💩💩if💩(fft::FftSupport💩*fft💩=💩parent_->AsFft())💩{
💩💩💩💩💩💩CheckError(fft->DoFft(this,💩plan,💩input,💩output));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(INFO)💩<<💩"attempting💩to💩perform💩FFT💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩FFT💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenFft(fft::Plan💩*plan,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&input,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*output)💩{
💩💩VLOG_CALL(PARAM(plan),💩PARAM(input),💩PARAM(output));

💩💩if💩(ok())💩{
💩💩💩💩if💩(fft::FftSupport💩*fft💩=💩parent_->AsFft())💩{
💩💩💩💩💩💩CheckError(fft->DoFft(this,💩plan,💩input,💩output));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(INFO)💩<<💩"attempting💩to💩perform💩FFT💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩FFT💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenFft(fft::Plan💩*plan,💩const💩DeviceMemory<float>💩&input,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<float>>💩*output)💩{
💩💩VLOG_CALL(PARAM(plan),💩PARAM(input),💩PARAM(output));

💩💩if💩(ok())💩{
💩💩💩💩if💩(fft::FftSupport💩*fft💩=💩parent_->AsFft())💩{
💩💩💩💩💩💩CheckError(fft->DoFft(this,💩plan,💩input,💩output));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(INFO)💩<<💩"attempting💩to💩perform💩FFT💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩FFT💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenFft(fft::Plan💩*plan,💩const💩DeviceMemory<double>💩&input,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<std::complex<double>>💩*output)💩{
💩💩VLOG_CALL(PARAM(plan),💩PARAM(input),💩PARAM(output));

💩💩if💩(ok())💩{
💩💩💩💩if💩(fft::FftSupport💩*fft💩=💩parent_->AsFft())💩{
💩💩💩💩💩💩CheckError(fft->DoFft(this,💩plan,💩input,💩output));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(INFO)💩<<💩"attempting💩to💩perform💩FFT💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩FFT💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenFft(fft::Plan💩*plan,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<float>>💩&input,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<float>💩*output)💩{
💩💩VLOG_CALL(PARAM(plan),💩PARAM(input),💩PARAM(output));

💩💩if💩(ok())💩{
💩💩💩💩if💩(fft::FftSupport💩*fft💩=💩parent_->AsFft())💩{
💩💩💩💩💩💩CheckError(fft->DoFft(this,💩plan,💩input,💩output));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(INFO)💩<<💩"attempting💩to💩perform💩FFT💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩FFT💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

Stream💩&Stream::ThenFft(fft::Plan💩*plan,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩const💩DeviceMemory<std::complex<double>>💩&input,
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩DeviceMemory<double>💩*output)💩{
💩💩VLOG_CALL(PARAM(plan),💩PARAM(input),💩PARAM(output));

💩💩if💩(ok())💩{
💩💩💩💩if💩(fft::FftSupport💩*fft💩=💩parent_->AsFft())💩{
💩💩💩💩💩💩CheckError(fft->DoFft(this,💩plan,💩input,💩output));
💩💩💩💩}💩else💩{
💩💩💩💩💩💩SetError();
💩💩💩💩💩💩LOG(INFO)💩<<💩"attempting💩to💩perform💩FFT💩operation💩using💩StreamExecutor💩"
💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩💩"without💩FFT💩support";
💩💩💩💩}
💩💩}
💩💩return💩*this;
}

//💩It💩looks💩confusing,💩but💩all💩this💩is💩doing💩is💩inserting💩a💩callback💩at💩the
//💩present💩point💩in💩the💩stream💩to💩then💩enqueue💩a💩task💩on💩the💩host💩executor.
Stream💩&Stream::ThenEnqueueOnBackgroundThread(
💩💩💩💩std::function<void(StreamExecutor💩*)>💩task)💩{
💩💩VLOG_CALL(PARAM(task));

💩💩StreamExecutor💩*stream_executor💩=💩this->parent_;
💩💩std::function<void()>💩bound_task💩=💩std::bind(task,💩stream_executor);

💩💩return💩ThenDoHostCallback([stream_executor,💩bound_task]()💩{
💩💩💩💩stream_executor->EnqueueOnBackgroundThread(bound_task);
💩💩});
}

bool💩Stream::BlockHostUntilDone()💩{
💩💩VLOG_CALL();

💩💩if💩(!ok())💩{
💩💩💩💩LOG(INFO)
💩💩💩💩💩💩💩💩<<💩"stream💩"💩<<💩this
💩💩💩💩💩💩💩💩<<💩"💩did💩not💩block💩host💩until💩done;💩was💩already💩in💩an💩error💩state";
💩💩💩💩return💩false;
💩💩}

💩💩{
💩💩💩💩//💩Wait💩until💩all💩active💩sub-streams💩have💩done💩their💩tasks.
💩💩💩💩mutex_lock💩lock{mu_};
💩💩💩💩for💩(auto💩&stream💩:💩sub_streams_)💩{
💩💩💩💩💩💩if💩(!stream.second)💩{
💩💩💩💩💩💩💩💩CheckError(stream.first->BlockHostUntilDone());
💩💩💩💩💩💩💩💩//💩Set💩this💩sub-stream💩as💩available.
💩💩💩💩💩💩💩💩stream.second💩=💩true;
💩💩💩💩💩💩}
💩💩💩💩}
💩💩}

💩💩temporary_memory_manager_.DeallocateFinalizedTemporaries();

💩💩CheckError(parent_->BlockHostUntilDone(this));
💩💩return💩ok();
}
