#pragma once
#include <cassert>

namespace blowin {
	namespace rangers {
		template<class IterT, class CallableT>
		constexpr void range(IterT start, const IterT finish, CallableT&& callable) {
			for (; start < finish; ++start)
				callable(start);
		}

		template<class T>
		struct fundamental_iterator {
		private:
			template<class TestT>
			using is_fundamental_iterator_t = typename std::is_same<TestT, fundamental_iterator>::type;
		public:
			static_assert(std::is_fundamental<T>::value &&
				!std::is_same<typename std::decay<T>::type, bool>::value,
				"Iterator type not fundamental");

			using iterator_category = std::random_access_iterator_tag;
			using value_type = T;
			using difference_type = T;
			using pointer = T;
			using reference = T;

			explicit constexpr fundamental_iterator(const T start) noexcept
				: hold_val_(start) {}
			template<class OthT, class = is_fundamental_iterator_t<OthT>>
			constexpr fundamental_iterator(OthT&& rgt) noexcept
				: hold_val_(rgt.hold_val_) {};
			template<class OthT, class = is_fundamental_iterator_t<OthT>>
			constexpr fundamental_iterator operator=(OthT&& rgt) noexcept {
				hold_val_ = rgt.hold_val_;
				return this;
			}
			constexpr T operator*() const noexcept { return hold_val_; }
			constexpr T operator->() const noexcept { return hold_val_; }

			constexpr T operator++(int) noexcept { return hold_val_++; }
			constexpr T operator++() noexcept { return ++hold_val_; }
			constexpr T operator--(int) noexcept { return hold_val_--; }
			constexpr T operator--() noexcept { return --hold_val_; }

			constexpr friend bool operator>(const fundamental_iterator lft, const fundamental_iterator rgt) noexcept {
				return lft.hold_val_ > rgt.hold_val_;
			}

			constexpr friend bool operator<=(const fundamental_iterator lft, const fundamental_iterator rgt) noexcept {
				return !(lft > rgt);
			}

			constexpr friend bool operator<(const fundamental_iterator lft, const fundamental_iterator rgt) noexcept {
				return rgt > lft;
			}

			constexpr friend bool operator>=(const fundamental_iterator lft, const fundamental_iterator rgt) noexcept {
				return !(lft < rgt);
			}

			constexpr friend bool operator==(const fundamental_iterator lft, const fundamental_iterator rgt) noexcept {
				return lft.hold_val_ == rgt.hold_val_;
			}

			constexpr friend bool operator!=(const fundamental_iterator lft, const fundamental_iterator rgt) noexcept {
				return !(lft == rgt);
			}

			constexpr T operator+=(const T offset) noexcept {
				return (hold_val_ += offset);
			}

			constexpr T operator+(const T offset) const noexcept {
				return (hold_val_ + offset);
			}

			constexpr T operator-=(const T offset) noexcept {
				return (hold_val_ -= offset);
			}

			constexpr T operator-(const T offset) const noexcept {
				return (hold_val_ - offset);
			}

			constexpr T operator[](const T offset) noexcept {
				return (hold_val_ += offset);
			}
		private:
			T hold_val_;
		};

		template<class T>
		struct fundamental_ranger {
		private:
			template<class TestT>
			using is_fundamental_range_t = typename std::is_same<TestT, fundamental_ranger>::type;
			using iter = fundamental_iterator<T>;
		public:
			constexpr fundamental_ranger(const T start, const T finish) noexcept
				: start_(start), finish_(finish) {}
			template<class OthT, class = is_fundamental_range_t<OthT>>
			constexpr fundamental_ranger(OthT&& rgt) noexcept
				: start_(rgt.start_), finish_(rgt.finish_) {}
			template<class OthT, class = is_fundamental_range_t<OthT>>
			constexpr fundamental_ranger operator=(T&& rgt) noexcept {
				start_ = rgt.start_;
				finish_ = rgt.finish_;
				return this;
			}
			constexpr const iter cbegin()	const noexcept { return iter(start_); }
			constexpr const iter cend()		const noexcept { return iter(finish_); }
			constexpr iter begin()		const noexcept { return iter(start_); }
			constexpr iter end()		const noexcept { return iter(finish_); }
		private:
			T start_;
			T finish_;
		};
		
		namespace ranger_t {
			using i8 = fundamental_ranger<int_fast8_t>;
			using i16 = fundamental_ranger<int_fast16_t>;
			using i32 = fundamental_ranger<int_fast32_t>;
			using i64 = fundamental_ranger<int_fast64_t>;
			using u8 = fundamental_ranger<uint_fast8_t>;
			using u16 = fundamental_ranger<uint_fast16_t>;
			using u32 = fundamental_ranger<uint_fast32_t>;
			using u64 = fundamental_ranger<uint_fast64_t>;
		}
		namespace iterator_t {
			using i8 = fundamental_iterator<int_fast8_t>;
			using i16 = fundamental_iterator<int_fast16_t>;
			using i32 = fundamental_iterator<int_fast32_t>;
			using i64 = fundamental_iterator<int_fast64_t>;
			using u8 = fundamental_iterator<uint_fast8_t>;
			using u16 = fundamental_iterator<uint_fast16_t>;
			using u32 = fundamental_iterator<uint_fast32_t>;
			using u64 = fundamental_iterator<uint_fast64_t>;
		}
	}
}
