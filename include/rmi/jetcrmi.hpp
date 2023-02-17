#pragma once

namespace jetc {
	struct Server {
		template<typename RetType,typename ...Args>
		friend void bind(Server& server,RetType(*Function)(Args...)) {
			
		}
	};

	struct Client {

	};

}