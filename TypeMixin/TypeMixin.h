#pragma once
#include <memory>

namespace TypeMixin
{
	class Type
	{
	public:
		using ID = int;

	private:
		static ID GetNextID() noexcept
		{
			static ID id = 0;
			return id++;
		}

	public:
		template <typename T>
		static const ID GetID() noexcept
		{
			static const ID id = GetNextID();
			return id;
		}

		template <typename T, typename U>
		static T* Cast(U* obj) noexcept
		{
			return reinterpret_cast<T*>(obj->Cast(GetID<T>()));
		}

		template <typename T, typename U>
		static const T* Cast(const U* obj) noexcept
		{
			return reinterpret_cast<const T*>(obj->Cast(GetID<T>()));
		}

		template<typename T, typename U>
		static std::shared_ptr<T> Pointer_Cast(const std::shared_ptr<U>& other) noexcept
		{
			const auto ptr = Cast<T>(other.get());
			if (ptr)
			{
				return (std::shared_ptr<T>(other, ptr));
			}
			return (std::shared_ptr<T>());
		}
	};

	template <typename ...T>
	class CastMixin;

	template <typename T>
	class CastMixin<T>
	{
	public:
		virtual const void* Cast(Type::ID id) const noexcept { return Type::GetID<T>() == id ? this : nullptr; }
		virtual void* Cast(Type::ID id) noexcept { return Type::GetID<T>() == id ? this : nullptr; }
	};

	template <typename T, typename ...Ts>
	class CastMixin<T, Ts...> : virtual public Ts...
	{
	public:
		virtual const void* Cast(Type::ID id) const noexcept
		{
			if (Type::GetID<T>() == id)
			{
				return this;
			}
			const void* d = nullptr;
			if ((... || (d = Ts::Cast(id))))
			{
				return d;
			}
			return nullptr;
		}

		virtual void* Cast(Type::ID id) noexcept
		{
			if (Type::GetID<T>() == id)
			{
				return this;
			}
			void* d = nullptr;
			if ((... || (d = Ts::Cast(id))))
			{
				return d;
			}
			return nullptr;
		}
	};
}
